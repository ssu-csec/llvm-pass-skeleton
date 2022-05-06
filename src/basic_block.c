int basic_block(int arg1, int arg2){
	int k, l, m;
	k = 1;
	l = k+1;
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
int main()
{
	basic_block(1,2);
}
