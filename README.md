Arduino Discordian Remote
=========================

Create some infrared havoc!

The __Arduino Discordian Remote__ is designed to create confusion and disruption at your local mall.

Build it, disguise it the best you can and leave it in front of a wall of TV sets.
It's designed to be activated by motion, and to send random infrared commands for the most popular TV brands for 10 seconds after a movement was detected.

Beware that this is just a draft, and not a mature project.
Also, beware that Illuminati will be after you, if you build it!

All hail discordian!

Electronic
----------

Minimum requirements are a PIR sensor (to detect motion)
and an infrared emitter, plus cables and some resistors.
Oh, an Arduino UNO will help. :-P

The discordian\_remote.fzz file contains the Fritzing circuit diagram.

For the PIR sensor I've used a Parallax SE-10 ( https://www.sparkfun.com/products/8630 )
and, for the IR emitter, I've just cannibalized an old TV remote.

Software
--------

Just copy the 'discordian\_remote' directory into your ~/sketchbook directory.
Most of it is commented, if you can understand my English.

Multimedia
----------

In the media directory, you'll find a picture that may help
you building the project (no, really: you're doing it for real?)

How it works
============

 - copy the 'discordian\_remote' directory into your ~/sketchbook directory
 - it needs the Arduino IRremote library, which can be found here: https://github.com/shirriff/Arduino-IRremote or https://github.com/alberanid/Arduino-IRremote
 - upload the program to your Arduino UNO board.
 - point it to one or more TV.
 - wait for the PIR to stabilize, and then move near it. Remember that it can send more or less 100 commands in 10 seconds and, being completely random and distributed over many different protocols, very few will be correct for your own TV set; modify the code (defining the *FORCED\_BRAND* identifier to limit the emitted commands to the ones of a single brand) to restrict the use of a single brand, if you want.
 - can you see the __fnords__?

Resources
=========

 - IRremote library: http://www.arcfn.com/2009/08/multi-protocol-infrared-remote-library.html
 - IR remotes knowledge base: http://www.sbprojects.com/knowledge/ir/index.php

Author
======

Davide Alberani <da@erlug.linux.it> (C) 2012
http://www.mimante.net/

License
=======

The code is covered by the GPL 3 or later license.
The picture and the circuit diagram are covered by a by-sa/3.0
creative commons license.

