# UBUNTU 14.04.3 64BIT

git clone https://github.com/linux-can/can-utils.git can-utils 

# fix dependencies
sudo apt-get install dh-autoreconf
cd can-utils
./autogen.sh
./configure
make
sudo make install

# make install output is like
# mkdir -p /usr/local/bin
# cp -f can-calc-bit-timing candump cansniffer cansend canplayer cangen canbusload log2long log2asc asc2log canlogserver bcmserver isotpdump isotprecv isotpsend isotpsniffer isotptun isotpserver isotpperf cangw slcan_attach slcand slcanpty canfdtest /usr/local/bin