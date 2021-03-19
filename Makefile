all:
	python ./scripts/mk_make.py;
	cd build; sudo make install -j11
