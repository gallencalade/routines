#!/bin/bash

PROJECT="project"
VERSION="${1}"
TIMESTAMP=`date "+%Y%m%d%H%M%S"`

if [ $# == 0 ]; then
  echo "No version number was specified"
  exit -1
fi

PACKAGE_NAME=${PROJECT}-${VERSION}-${TIMESTAMP}
TAR_GZ_NAME=${PACKAGE_NAME}.tar.gz

mkdir -p ${PACKAGE_NAME}

tar -zcvhf ${TAR_GZ_NAME} ${PACKAGE_NAME}

rm -rf ${PACKAGE_NAME}
