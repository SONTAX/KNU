#!/usr/bin/ruby
# frozen_string_literal: true

def f1(x)
  1.0 / ((x + 1) * Math.sqrt(x**2 + 1))
end

def f2(x)
  x * Math.atan(x)
end

def prm(left, right, func, eps)
  h = (right - left) / eps
  sum = 0
  (1..eps).each do |i|
    x = left + i * h - h / 2
    sum += f1(x) if func == 1
    sum += f2(x) if func == 2
  end
  h * sum
end

def trp(left, right, func, eps)
  h = (right - left) / eps
  sum_a = f1(left) / 2 if func == 1
  sum_a = f2(left) / 2 if func == 2
  sum_b = f1(right) / 2 if func == 1
  sum_b = f2(right) / 2 if func == 2
  (1..(eps / 2)).each do |i|
    sum_a += f1(left + h * i) if func == 1
    sum_a += f2(left + h * i) if func == 2
    sum_b += f1(right - h * i) if func == 1
    sum_b += f2(right - h * i) if func == 2
  end
  h * (sum_a + sum_b)
end

puts 'prm for f1: ', prm(0.0, 0.6, 1, 100_000)
puts 'prm for f2: ', prm(0.2, 1.6, 2, 100_000)
puts 'trp for f1: ', trp(0.0, 0.6, 1, 100_000)
puts 'trp for f2: ', trp(0.2, 1.6, 2, 100_000)
