# Simple Multithread Server

## Goal
The goal of this repository is to join my knowloge about sockets and pthreads to create a very simple multithread server

## Benchmark
`ab -n 1000 -c 50 http://localhost:18000/test.html`

### Single Thread
Benchmarking localhost (be patient)
Completed 100 requests
Completed 200 requests
Completed 300 requests
Completed 400 requests
Completed 500 requests
Completed 600 requests
Completed 700 requests
Completed 800 requests
Completed 900 requests
Completed 1000 requests
Finished 1000 requests


Server Software:        
Server Hostname:        localhost
Server Port:            18000

Document Path:          /test.html
Document Length:        0 bytes

Concurrency Level:      50
Time taken for tests:   100.675 seconds
Complete requests:      1000
Failed requests:        0
Total transferred:      155000 bytes
HTML transferred:       0 bytes
Requests per second:    9.93 [#/sec] (mean)
Time per request:       5033.768 [ms] (mean)
Time per request:       100.675 [ms] (mean, across all concurrent requests)
Transfer rate:          1.50 [Kbytes/sec] received

Connection Times (ms)
              min  mean[+/-sd] median   max
Connect:        0    0   0.0      0       0
Processing:   100  100   0.2    100     101
Waiting:        0    0   0.1      0       1
Total:        100  101   0.2    101     101

Percentage of the requests served within a certain time (ms)
  50%    101
  66%    101
  75%    101
  80%    101
  90%    101
  95%    101
  98%    101
  99%    101
 100%    101 (longest request)

### Multithread
Benchmarking localhost (be patient)
Completed 100 requests
Completed 200 requests
Completed 300 requests
Completed 400 requests
Completed 500 requests
Completed 600 requests
Completed 700 requests
Completed 800 requests
Completed 900 requests
Completed 1000 requests
Finished 1000 requests


Server Software:        
Server Hostname:        localhost
Server Port:            18000

Document Path:          /test.html
Document Length:        0 bytes

Concurrency Level:      50
Time taken for tests:   0.225 seconds
Complete requests:      1000
Failed requests:        0
Total transferred:      155000 bytes
HTML transferred:       0 bytes
Requests per second:    4435.10 [#/sec] (mean)
Time per request:       11.274 [ms] (mean)
Time per request:       0.225 [ms] (mean, across all concurrent requests)
Transfer rate:          671.33 [Kbytes/sec] received

Connection Times (ms)
              min  mean[+/-sd] median   max
Connect:        0    0   0.0      0       0
Processing:     0    0   0.0      0       1
Waiting:        0    0   0.0      0       0
Total:          0    0   0.0      0       1

Percentage of the requests served within a certain time (ms)
  50%      0
  66%      0
  75%      0
  80%      0
  90%      0
  95%      0
  98%      0
  99%      0
 100%      1 (longest request)

