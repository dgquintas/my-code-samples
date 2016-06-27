provider heapsort {
	 probe input_start();
	 probe input_done(int);	/* (int number of items) */
	 probe buffer_resize_start();
	 probe buffer_resize_done();
	 probe output_start(int);	/* (int number of items) */
	 probe output_done();
	 probe heap_place(int, int);	/* (int position, int value) */
	 probe heap_build_start();
	 probe heap_build_done();
};
