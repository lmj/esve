
require 'find'
require 'fileutils'
require 'pp'

SRC_MESSAGE = "tick"

MESSAGES = [
   "draw",
   "update",
   "handle",
   "tick",
   "compute",
]

specs = MESSAGES.delete_if { |x|
   x == SRC_MESSAGE
}.map { |message|
   [
      "hxx",
      "cxx",
   ].map { |ext|
      [
         "#{message.capitalize}_Node.#{ext}",
         "#{message.capitalize}_Receiver.#{ext}",
         "#{message.capitalize}_Receiver_Stowed.#{ext}",
         "#{message.capitalize}_Sender.#{ext}",
         "#{message.capitalize}_Sender_Delegator.#{ext}",
         "#{message.capitalize}_Sender_Stowed.#{ext}",
         "impl/#{message.capitalize}_Node.#{ext}",
         "impl/#{message.capitalize}_Receiver.#{ext}",
         "impl/#{message.capitalize}_Sender.#{ext}",
      ].map { |filename|
         {
            :src_message => SRC_MESSAGE,
            :dst_message => message,
            :src_filename => filename.sub(message.capitalize,
                                          SRC_MESSAGE.capitalize),
            :dst_filename => filename,
         }
      }
   }
}.flatten

Dir.chdir("esve/message") {
   specs.each { |spec|
      puts "#{spec[:src_filename]} --> #{spec[:dst_filename]}"
      open(spec[:dst_filename], "w") { |dst|
         dst.print(
            File.open(spec[:src_filename]) { |src|
                src.read
            }.gsub(spec[:src_message],
                   spec[:dst_message]).
              gsub(spec[:src_message].capitalize,
                   spec[:dst_message].capitalize))
      }
   }
}

system("patch -p0 -R < make/message-modify.patch")
