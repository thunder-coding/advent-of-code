validate_signal() {
  if echo "${1}" | grep -qE "[0-9]+" && [ "${1}" -gt $((2 ** 16 - 1)) ]; then
    return 1
  fi
}
parse() {
  while read -r line || [ -n "${line}" ]; do
    # Remove trailing newline
    line=${line%$'\n'}
    local a=
    local b=
    local gate=
    local dest=
    if echo "$line" | grep -qE "^NOT ([0-9]+|[a-z]+) -> [a-z]+$"; then
      gate="NOT"
      a="${line%%" ->"*}"
      a="${a#"NOT "}"
      dest="${line##*" -> "}"
    elif echo "$line" | grep -qE "^([0-9]+|[a-z]+) -> [a-z]+$"; then
      gate="COPY"
      a="${line%%" ->"*}"
      dest="${line##*" -> "}"
    elif echo "$line" | grep -qE "^([0-9]+|[a-z]+) (AND|OR|LSHIFT|RSHIFT) ([0-9]+|[a-z]+) -> [a-z]+$"; then
      dest="${line##*" -> "}"
      a="${line%%" "*}"
      b="${line%%" ->"*}"
      b="${b##*" "}"
      gate="${line:$((${#a} + 1)):-$((${#b} + 1 + "$(expr length " -> ")" + ${#dest}))}"
    else
      echo "Error parsing line '${line}'"
      return 1
    fi
    if [[ -v wires["${dest}0"] ]]; then
      echo "Wire '${dest}' can recieve signal from only one source"
      return 1
    fi
    validate_signal "$a"
    validate_signal "$b"
    wires["${dest}"0]="${a}"
    wires["${dest}"1]="${b}"
    wires["${dest}"2]="${gate}"
    wires["${dest}"3]="NOT_CALCULATED"
    wires["${dest}"4]=0
  done <./2015/07/input.txt
}

calculate() {
  if ! [[ -v wires["${1}"0] ]]; then
    echo "Wire '${1}' not found in circuit"
    return 1
  fi
  if [ "${wires["${1}"3]}" = "CALCULATED" ]; then
    echo "${wires["${1}"4]}"
    return 0
  elif [ "${wires["${1}"3]}" = "CALCULATING" ]; then
    echo "Recursion detected when calculating for '${1}'"
    return 1
  fi

  wires["${1}"3]="CALCULATING"
  local a="${wires["${1}"0]}"
  if echo "$a" | grep -qE '[a-z]+'; then
    local a_tmp
    a_tmp="$(mktemp)"
    calculate "$a" >"$a_tmp"
    a="$(cat "$a_tmp")"
    rm "$a_tmp"
  fi
  local b="${wires["${1}"1]}"
  local gate="${wires["${1}"2]}"
  case "$gate" in
  "NOT")
    wires["${1}"4]=$((~a & 0xffff))
    ;;
  "COPY")
    wires["${1}"4]=$((a))
    ;;
  esac
  if echo "$b" | grep -qE '[a-z]+'; then
    local b_tmp
    b_tmp="$(mktemp)"
    calculate "$b" >"$b_tmp"
    b="$(cat "$b_tmp")"
    rm "$b_tmp"
  fi
  case "$gate" in
  "AND")
    wires["${1}"4]=$((a & b))
    ;;
  "OR")
    wires["${1}"4]=$((a | b))
    ;;
  "LSHIFT")
    wires["${1}"4]=$(((a << b) & 0xffff))
    ;;
  "RSHIFT")
    wires["${1}"4]=$((a >> b))
    ;;
  esac
  wires["${1}"3]="CALCULATED"
  echo "${wires["${1}"4]}"
}
