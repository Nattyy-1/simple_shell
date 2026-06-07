#!/bin/bash
# Functional test suite for the simple_shell (hsh).
#
# Runs a series of inputs through ./hsh and checks observable behaviour:
# stdout contents, stderr contents, and process exit codes.
#
# Usage: tests/run_tests.sh   (works from any directory)

cd "$(dirname "$0")/.." || exit 1

HSH=./hsh
pass=0
fail=0

make >/dev/null 2>&1 || { echo "build failed"; exit 1; }

# assert_out NAME INPUT EXPECTED — stdout must contain EXPECTED
assert_out()
{
	local out
	out=$(printf '%b' "$2" | $HSH 2>/dev/null)
	if echo "$out" | grep -qF "$3"; then
		echo "PASS: $1"; pass=$((pass + 1))
	else
		echo "FAIL: $1 (expected stdout to contain '$3', got '$out')"
		fail=$((fail + 1))
	fi
}

# assert_absent NAME INPUT PATTERN — stdout must NOT contain PATTERN
assert_absent()
{
	local out
	out=$(printf '%b' "$2" | $HSH 2>/dev/null)
	if echo "$out" | grep -qF "$3"; then
		echo "FAIL: $1 (did not expect '$3' in stdout)"
		fail=$((fail + 1))
	else
		echo "PASS: $1"; pass=$((pass + 1))
	fi
}

# assert_err NAME INPUT EXPECTED — stderr must contain EXPECTED
assert_err()
{
	local err
	err=$(printf '%b' "$2" | $HSH 2>&1 1>/dev/null)
	if echo "$err" | grep -qF "$3"; then
		echo "PASS: $1"; pass=$((pass + 1))
	else
		echo "FAIL: $1 (expected stderr to contain '$3', got '$err')"
		fail=$((fail + 1))
	fi
}

# assert_exit NAME INPUT EXPECTED_CODE — process must exit with EXPECTED_CODE
assert_exit()
{
	printf '%b' "$2" | $HSH >/dev/null 2>&1
	local code=$?
	if [ "$code" -eq "$3" ]; then
		echo "PASS: $1"; pass=$((pass + 1))
	else
		echo "FAIL: $1 (expected exit $3, got $code)"
		fail=$((fail + 1))
	fi
}

echo "=== external commands & PATH ==="
assert_out  "absolute path"        "/bin/echo hello\n"          "hello"
assert_out  "PATH lookup"          "echo viapath\n"             "viapath"
assert_out  "command with args"    "/bin/echo a b c\n"          "a b c"
assert_err  "command not found"    "nosuchcmd123\n"             "not found"

echo "=== comments ==="
assert_out  "inline comment"       "/bin/echo keep # drop\n"    "keep"
assert_absent "comment text gone"  "/bin/echo keep # dropme\n"  "dropme"
assert_out  "command after #line"  "# just a comment\necho ok\n" "ok"

echo "=== multiple commands (;) ==="
assert_out  "first of chain"       "echo one; echo two\n"       "one"
assert_out  "second of chain"      "echo one; echo two\n"       "two"
assert_out  "chain survives error" "nosuchcmd; echo after\n"    "after"

echo "=== whitespace ==="
assert_out  "leading spaces"       "   echo lead\n"             "lead"
assert_out  "interior spaces"      "/bin/echo  a   b\n"         "a b"
assert_out  "blank lines ignored"  "\n\n   \necho done\n"       "done"

echo "=== builtin: env / setenv / unsetenv ==="
assert_out  "setenv shows in env"  "setenv TV hello42; env\n"   "TV=hello42"
assert_absent "unsetenv removes"   "setenv TV x; unsetenv TV; env\n" "TV=x"
assert_out  "setenv update value"  "setenv TV one; setenv TV two; env\n" "TV=two"

echo "=== builtin: cd ==="
assert_out  "cd absolute"          "cd /tmp; /bin/pwd\n"        "/tmp"
assert_out  "cd dash prints dir"   "cd /tmp; cd /; cd -\n"      "/tmp"
assert_err  "cd bad dir errors"    "cd /no_such_dir_xyz\n"      "can't cd to"

echo "=== builtin: exit ==="
assert_exit "exit no arg"          "exit\n"                     0
assert_exit "exit with code"       "exit 42\n"                  42
assert_exit "EOF clean exit"       "echo hi\n"                  0

echo ""
echo "================================"
echo "Total: $((pass + fail))  Passed: $pass  Failed: $fail"
[ "$fail" -eq 0 ]
