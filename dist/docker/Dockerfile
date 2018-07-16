FROM ubuntu:18.04

RUN apt-get update -y -q \
 && apt-get install -y -qq --no-install-recommends cmake make g++ libfontconfig1-dev libsfml-dev \
 && apt-get autoremove -y \
 && apt-get clean && apt-get autoclean \
 && rm -rf /tmp/* /var/tmp/* \
 && rm -rf /var/lib/apt/lists/* \
 && rm -f /var/cache/apt/archives/*.deb /var/cache/apt/archives/partial/*.deb /var/cache/apt/*.bin
