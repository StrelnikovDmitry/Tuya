int get_length(int n) {
	if (n < 100000) {
		if (n < 1000) {
			if (n < 100) {
				if (n < 10) {
					return 1;
				} 
				else {
					return 2;
				}
			}
			else {
				return 3;
			}
		}
		else {
			if (n < 10000) {
				return 4;
			}
			else {
				return 5;
			}
		}
	}
	else {
		if (n < 100000000) {
			if (n < 10000000) {
				if (n < 1000000) {
					return 6;
				}
				else {
					return 7;
				}
			}
			else {
				return 8;
			}
		}
		else {
			if (n < 1000000000) {
				return 9;
			}
			else {
				return 10;
			}
		}
	}
}

int moving_cursor_cost(int x, int y) {
	return 4+get_length(x)+get_length(y);	
}
