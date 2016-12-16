#!/bin/bash

# You'll need to edit this if your Biocellion is installed elsewhere
BIOCELLION_BASE=${HOME}/biocellion

BASE_NAME=vascular-network
MODEL_NAME=model-${BASE_NAME}
XML_FILE=${BASE_NAME}.xml
OUTPUT_NAME=output
RUN_LOG=${XML_FILE}.out
MAIN=framework/main

# Go to the model directory
dir=`dirname $0`
model_dir=`pwd`

cd "$dir"
if [ `pwd` != "$model_dir" ]; then
    echo "Did not cd to '$model_dir'"
    exit 1
fi

# Setup the output directory in the model directory
mkdir -p $OUTPUT_NAME
if [ ! -d "$OUTPUT_NAME" ]; then
    echo "Did not make '$OUTPUT_NAME'"
    exit 1
fi
rm -f $OUTPUT_NAME/*

# Setup XML and output files, directories
if [ ! -d "$BIOCELLION_BASE/$MAIN" ]; then
    echo "$BIOCELLION_BASE/$MAIN is not a directory"
    exit 1
fi
cp -f $XML_FILE $BIOCELLION_BASE/$MAIN/

# Move to the biocellion's libmodel
if [ ! -d "$BIOCELLION_BASE/libmodel" ]; then
    echo "$BIOCELLION_BASE/libmodel is not a directory."
    exit 1
fi
cd $BIOCELLION_BASE/libmodel
if [ `pwd` != "$BIOCELLION_BASE/libmodel" ]; then
    echo "Did not cd to '$BIOCELLION_BASE/libmodel'"
    exit 1
fi

# Copy/Link the model in correctly
if [ -h model ]; then
    rm model
fi
if [ ! -d model-${BASE_NAME} ]; then
    mkdir model-${BASE_NAME}
fi
for f in `ls $model_dir`; do
    if [ -L model-${BASE_NAME}/$f ]; then
	rm model-${BASE_NAME}/$f
    fi
    ln -s $model_dir/$f model-${BASE_NAME}/
done
if [ -e model ]; then
    echo `pwd`/model already exists.
    exit 1
fi
ln -s model-${BASE_NAME} model

# build the model library
#make clean
make

# go to the run location
cd ..
cd $MAIN
if [ `pwd` != "$BIOCELLION_BASE/$MAIN" ]; then
    echo "Did not cd to '$BIOCELLION_BASE/$MAIN'"
    exit 1
fi

# run the simulation
/usr/bin/time ./biocellion.DP.SPAGENT.OPT $XML_FILE > $RUN_LOG 2>&1
#./biocellion.DP.SPAGENT.OPT $XML_FILE


# clean up libmodel
cd $BIOCELLION_BASE/libmodel
if [ `pwd` != "$BIOCELLION_BASE/libmodel" ]; then
    echo "Did not cd to '$BIOCELLION_BASE/libmodel'"
    exit 1
fi
if [ -h model ]; then
    rm model
fi

if [ -d model-${BASE_NAME} ]; then
    for f in `ls model-${BASE_NAME}`; do
	if [ -L model-${BASE_NAME}/$f ]; then
	    rm model-${BASE_NAME}/$f
	fi
    done
    rmdir model-${BASE_NAME}
fi

exit 0
