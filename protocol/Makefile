
ROOT_DIR := $(shell dirname $(realpath $(lastword $(MAKEFILE_LIST))))
# Path to the nanopb root directory
NANOPB_DIR :=  $(ROOT_DIR)/../libs/nanopb

# Check if we are running on Windows
ifdef windir
WINDOWS = 1
endif
ifdef WINDIR
WINDOWS = 1
endif

# Check whether to use binary version of nanopb_generator or the
# system-supplied python interpreter.
ifneq "$(wildcard $(NANOPB_DIR)/generator-bin)" ""
	# Binary package
	PROTOC = $(NANOPB_DIR)/generator-bin/protoc
	PROTOC_OPTS = 
else
	# Source only or git checkout
	PROTOC = protoc
	ifdef WINDOWS
		PROTOC_OPTS = --plugin=protoc-gen-nanopb=$(NANOPB_DIR)/generator/protoc-gen-nanopb.bat
	else
		PROTOC_OPTS = --plugin=protoc-gen-nanopb=$(NANOPB_DIR)/generator/protoc-gen-nanopb
	endif
endif

all: car_to_server.pb.c server_to_car.pb.c common.pb.c

%.pb.c %.pb.h: %.proto $(wildcard %.options)
	$(PROTOC) $(PROTOC_OPTS) --nanopb_out=. $<

clean:
	rm -f *.pb.c *.pb.h


