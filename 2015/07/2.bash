set -e
. ./2015/07/circuit.bash
declare -Ag wires
parse
b=$(calculate a)
for key in "${!wires[@]}"; do
  wires["${key}3"]="NOT_CALCULATED"
done

if ! [[ -v wires["b0"] ]]; then
  echo "Wire 'b' not present in the circuit"
  exit 1
fi

wires["b3"]="CALCULATED"
wires["b4"]="$b"

calculate a
