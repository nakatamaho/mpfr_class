MPFR_VERSION=4.2.1
GMP_VERSION=6.3.0
VERSION=1.3.1
export CC=gcc-12
export CXX=g++-12

WRKDIR=/home/docker/mpfrcxx/setup/work_mpc
ARCHIVEDIR=/home/docker/mpfrcxx/archives/

rm -rf $WRKDIR
mkdir -p $WRKDIR
cd $WRKDIR
tar xvf $ARCHIVEDIR/mpc-${VERSION}.tar.gz
cd mpc-${VERSION}
./configure --with-gmp=/home/docker/mpfrcxx/i/GMP-${GMP_VERSION} --with-mpfr=/home/docker/mpfrcxx/i/MPFR-${MPFR_VERSION} --prefix=/home/docker/mpfrcxx/i/MPC-${VERSION}
make -j`nproc`
make check
make install
cd ..
rm -rf $WRKDIR
