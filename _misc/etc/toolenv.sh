#!/bin/sh

#--- T-Kernel ---
export BD=${PRJPATH}/tkernel_source
export GNUs=/usr

if test ${TC_KIND} = SH_GCC_TF
then
  echo "--- SH7760 GCC TF ---"
  export GNU_BD=/usr/local/tool/sh-elf
  export _GNU_CONFIG=sh-unknown-tkernel-
  export GNUsh=${GNU_BD}/sh-unknown-tkernel
  export GCC_EXEC_PREFIX=$GNU_BD/lib/gcc-lib/
elif test ${TC_KIND} = SH_GCC_KPIT
then
  echo "--- SH7760 GCC KPIT(Renesas GNU Tool) ---"
  export GNU_BD=${C_DRV}/Renesas/e2_studio/GNUSHv13.01-ELF/sh-elf
  export _GNU_CONFIG=sh-elf-
  export GNUsh=${GNU_BD}/sh-elf
  export GCC_EXEC_PREFIX=$GNU_BD/lib/gcc/
  export PATH=${GNU_BD}/bin:$PATH
elif test ${TC_KIND} = ARM_GCC_TF
then
  echo "--- ARM GCC TF ---"
  export GNU_BD=/usr/local/tool/arm_2-elf
  export _GNU_CONFIG=arm_2-unknown-tkernel-
  export GNUARM_2=${GNU_BD}/arm_2-unknown-tkernel
elif test ${TC_KIND} = ARM_GCC_KPIT
then
  echo "--- ARM GCC KPIT ---"
  # export GNU_BD='/C/Program Files (x86)/KPIT/GNUARM-NONEv14.02-EABI/arm-none-eabi/arm-none-eabi'
  export GNU_BD='/C/Program Files (x86)/KPIT/GNUARM-NONEv16.01-EABI/arm-none-eabi/arm-none-eabi'
  export _GNU_CONFIG=arm-none-eabi-
  export PATH=${GNU_BD}/bin:$PATH
elif test ${TC_KIND} = ARM_GCC_EMB
then
  echo "--- GNU ARM Embedded ---"
  # export GNU_BD='/C/Program Files (x86)/GNU Tools ARM Embedded/4.9 2015q3'
  # export GNU_BD='/C/Program Files (x86)/GNU Tools ARM Embedded/5.4 2016q2'
  # export GNU_BD='/C/Program Files (x86)/GNU Tools ARM Embedded/5.4 2016q3'
  export GNU_BD='/C/Program Files (x86)/GNU Tools ARM Embedded/6 2017-q2-update'
  # export GNU_BD='/C/Program Files (x86)/GNU Tools ARM Embedded/7 2017-q4-major'
  export _GNU_CONFIG=arm-none-eabi-
  export PATH=${GNU_BD}/bin:$PATH
elif test ${TC_KIND} = MAC_ARM_GCC_EMB
then
  echo "--- macOS GNU ARM Embedded ---"
  export GNU_BD=/usr/local
  #export GNU_BD=/opt/gnu_arm/gcc-arm-none-eabi-5_4-2016q2
  #export GNU_BD=/opt/gnuarm/gcc-arm-none-eabi-7-2017-q4-major
  export _GNU_CONFIG=arm-none-eabi-
  #export PATH=$PATH:${GNU_BD}/bin
elif test ${TC_KIND} = LINUX_ARM_GCC_EMB
then
  echo "--- Linux GNU ARM Embedded ---"
  #export GNU_BD=/opt/gnuarm/gcc-arm-none-eabi-7-2017-q4-major
  export GNU_BD=/usr
  export _GNU_CONFIG=arm-none-eabi-
  #export PATH=$PATH:${GNU_BD}/bin
elif test ${TC_KIND} = TOOL
then
  echo "--- TOOL ---"
else
  # for ${TC_KIND} = NONE
  echo "" > /dev/null
fi

if [ ! -z "${BD}" ]; then
    alias cdtk='cd ${BD}'
    alias tk-put-rpi='${BD}/../_misc/etc/tftp-put-rpi'
fi
if [ ! -z "${GNU_BD}" ]; then
    alias gdbarm='"${GNU_BD}/bin/${_GNU_CONFIG}gdb"'
fi
