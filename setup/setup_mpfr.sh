VERSION=4.2.1
GMP_VERSION=6.3.0  
export CC=gcc-12
export CXX=g++-12

WRKDIR=/home/docker/mpfr_class/setup/work_mpfr
ARCHIVEDIR=/home/docker/mpfr_class/archives/

rm -rf $WRKDIR
mkdir -p $WRKDIR
cd $WRKDIR
tar xvf $ARCHIVEDIR/mpfr-${VERSION}.tar.xz
cd mpfr-${VERSION}
./configure --with-gmp=/home/docker/mpfr_class/i/GMP-${GMP_VERSION}  --prefix=/home/docker/mpfr_class/i/MPFR-${VERSION}
make -j`nproc`
make check
make install
cd ..
rm -rf $WRKDIR
