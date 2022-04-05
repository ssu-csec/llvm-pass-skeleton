int basic_block(int arg1, int arg2){
	int k, l, m;
	k = arg1;
	l = arg2;
	if (k == l) {
		m = arg1 * arg2;
	}
	else if (k > l) {
		m = arg2 * arg2;
	}
	else {
		m = k + l;
	}

	if (m > 100) {
		return 0;
	}
	else {
		return m;
	}
}
