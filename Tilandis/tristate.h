/*
 * Generic tristate object header
 * Copyright © 2016 Nicholas O'Connor
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated
 * documentation files (the "Software"), to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and
 * to permit persons to whom the Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all copies or substantial portions of
 * the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO
 * THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF
 * CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
 * IN THE SOFTWARE.
 *
 * (tristate.h is considered to be a separate project from whatever source code you happen to have found it in.
 * take it and use it regardless of what anyone else says.)
 */

#pragma once
#ifndef __TRISTATE_H
#define __TRISTATE_H

// Generic tristate object.
enum tristate {
	False,
	True,
	Mixed
};

tristate operator==(tristate& lhs, bool& rhs) {
	if (lhs == True) {
		switch (rhs) {
		case true:
			return True;
		case false:
			return False;
		}
	} else if (lhs == False) {
		switch (rhs) {
		case true:
			return False;
		case false:
			return True;
		}
	} else { // Mixed
#ifdef TRISTATE_MIXED_IS_FALSE
		switch (rhs) {
		case true:
			return False;
		case false:
			return True;
		}
#else
		switch (rhs) {
		case true:
			return True;
		case false:
			return False;
		}
#endif
	}
}

bool operator==(bool& lhs, tristate& rhs) {
	if (rhs == True) {
		switch (lhs) {
		case true:
			return True;
		case false:
			return False;
		}
	}
	else if (rhs == False) {
		switch (lhs) {
		case true:
			return False;
		case false:
			return True;
		}
	}
	else { // Mixed
#ifdef TRISTATE_MIXED_IS_FALSE
		switch (lhs) {
		case true:
			return False;
		case false:
			return True;
		}
#else
		switch (lhs) {
		case true:
			return True;
		case false:
			return False;
		}
#endif
	}
}

#endif // !__TRISTATE_H
