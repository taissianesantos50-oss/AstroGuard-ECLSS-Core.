# v1.4 Tests

Compile:
gcc src/health_monitor.c tests/test_health_monitor.c -I src -o test_health_monitor

Run:
./test_health_monitor

A successful run returns exit code 0. These tests verify deterministic demonstration rules only and do not establish medical validity.
