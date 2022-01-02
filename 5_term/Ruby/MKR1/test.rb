#!/usr/bin/ruby
# frozen_string_literal: true

a = 312
b = 2
c = 31
puts ~(a | b) & (a ^ c)
