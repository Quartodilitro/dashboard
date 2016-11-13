# Copyright 2016 Quartodilitro Team Unipd
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
# http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.



VCAN=$1  # get name of canbus inteface by cmd argument

ip link del $VCAN  # trash previous canbus
modprobe can
modprobe can_raw
modprobe vcan  # bring it up
ip link add dev $VCAN type vcan  # add new device
ip link set up $VCAN  # link
ip link show $VCAN  # show in devices
