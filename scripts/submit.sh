#!/bin/bash
source /swshare/ROOT/root_v5.34.18_slc6_amd64/bin/thisroot.sh

cd /shome/cheidegg/p/MPAF_forSF

source setup.sh
analysis -c $1
