MAKE = make

all: build_engine build_engineTest build_client

build_engine: 
	$(MAKE) -C engine all

build_engineTest:
	$(MAKE) -C engineTest all

build_client: build_engine
	$(MAKE) -C client all

clean: clean_engine clean_engineTest clean_client

clean_engine: 
	$(MAKE) -C engine clean

clean_engineTest:
	$(MAKE) -C engineTest clean

clean_client: 
	$(MAKE) -C client clean

.PHONY: clean_engine clean_engineTest clean_client

