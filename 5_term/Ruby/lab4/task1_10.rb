#!/usr/bin/ruby
# frozen_string_literal: true

a = Array.new(12)
b = Array.new(12)

i = 0
while i < 12
  a[i] = rand(10)
  b[i] = rand(10)
  i += 1
end

temp1 = Array.new(0)
temp2 = Array.new(0)
temp3 = Array.new(0)
temp4 = Array.new(0)

b.each do |x|
  temp1.push(x) if x.even?
  temp2.push(x) if x.odd?
end

a.each do |x|
  temp3.push(x) if x.odd?
  temp4.push(x) if x.even?
end

c = temp1 + temp2 + temp3 + temp4

puts 'a: '
i = 0
while i < 12
  printf("#{a[i]}\t")
  i += 1
end

puts '', 'b: '
i = 0
while i < 12
  printf("#{b[i]}\t")
  i += 1
end

puts '', 'c: '
i = 0
while i < 24
  printf("#{c[i]}\t")
  i += 1
end
