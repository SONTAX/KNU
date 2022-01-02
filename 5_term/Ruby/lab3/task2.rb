#!/usr/bin/ruby
# frozen_string_literal: true

# 2

x = -4.1
if x > -4 && x <= 0
  puts 'y: ', ((x - 2.0).abs / (x**2.0 * Math.cos(x)))**(1.0 / 7.0)
elsif x.positive? && x <= 12
  puts 'y: ', 1.0 / (Math.tan(x + 1.0 / Math.exp(x)) / Math.sin(x)**2)**(2.0 / 7.0)
elsif x > 12 || x < -4
  puts 'y: ', 1.0 / (1.0 + x / (1.0 + x / (1.0 + x)))
end
