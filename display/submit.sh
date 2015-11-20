#!/bin/bash
source /swshare/ROOT/root_v5.34.18_slc6_amd64/bin/thisroot.sh
cd /shome/mmarionn/MPAF
source setup.sh
cd display

root -b cards/tmpFiles/$1.C > /shome/mmarionn/MPAF/workdir/logs/$1.log