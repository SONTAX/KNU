#!/usr/bin/ruby
# frozen_string_literal: true

class Train
  @@id = 1

  def initialize(destination, time, places_number)
    @destination = destination
    @time = time
    @places_number = places_number
    @train_number = @@id
    @@id += 1
  end

  def setDestination(new_destination)
    @destination = new_destination
  end

  def getDestination
    @destination
  end

  def setTrainNumber(new_train_number)
    @train_number = new_train_number
  end

  def getTrainNumber
    @train_number
  end

  def setTime(new_time)
    @time = new_time
  end

  def getTime
    @time
  end

  def setNumberOfPlaces(new_places_number)
    @places_number = new_places_number
  end

  def getNumberOfPlaces
    @places_number
  end

  def toString
    "Train number #{@train_number} goes to #{@destination}. Departure time is: #{@time}.
          Number of places (general, compartment, seat card, lux): #{@places_number}\n"
  end
end

class TrainController
  def initialize(trains_array)
    @trains_array = trains_array
    @result_array = Array.new(0)
  end

  def taskA(my_destination)
    @trains_array.each do |x|
      @result_array.push(x.toString) if x.getDestination == my_destination
    end
    printResult
  end

  def taskB(my_destination, my_time)
    @trains_array.each do |x|
      @result_array.push(x.toString) if x.getDestination == my_destination && x.getTime > my_time
    end
    printResult
  end

  def taskC(my_destination)
    @trains_array.each do |x|
      @result_array.push(x.toString) if x.getDestination == my_destination && x.getNumberOfPlaces[0].positive?
    end
    printResult
  end

  def printResult
    puts @result_array
    @result_array = Array.new(0)
  end
end

train1 = Train.new('Lviv', 12, [12, 4, 6, 2])
train2 = Train.new('Lviv', 2, [0, 8, 3, 22])
train3 = Train.new('Lviv', 15, [23, 12, 7, 1])
train4 = Train.new('Lviv', 20, [36, 0, 0, 10])
train5 = Train.new('Odessa', 16, [0, 0, 36, 18])
train6 = Train.new('Odessa', 12, [0, 72, 60, 22])
train7 = Train.new('Odessa', 22, [80, 0, 32, 0])
train8 = Train.new('Kherson', 7, [20, 40, 60, 80])
train9 = Train.new('Kherson', 17, [9, 27, 18, 36])
controller = TrainController.new([train1, train2, train3, train4, train5, train6, train7, train8, train9])
puts 'task a: '
controller.taskA('Kherson')
puts '', 'task b: '
controller.taskB('Odessa', 14)
puts '', 'task c: '
controller.taskC('Lviv')
