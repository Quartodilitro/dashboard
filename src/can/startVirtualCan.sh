VCAN=$1  # get name of canbus inteface by cmd argument

ip link del $VCAN  # trash previous canbus
modprobe can
modprobe can_raw
modprobe vcan  # bring it up
ip link add dev $VCAN type vcan  # add new device
ip link set up $VCAN  # link
ip link show $VCAN  # show in devices
