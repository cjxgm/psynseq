# psynseq - Procedural Synthesizer & Sequencer
This program is written in C with OpenGL and OSS.<br>
by eXerigumo Clanjor (哆啦比猫/兰威举)<br>
Licensed Under GPLv2. *ABSOLUTELY NO WARRANTY!*

## Build

	./cjbs			# build without fullscreen
	./cjbs -f		# build with    fullscreen

## Run
If you have oss, run

	./psynseq

If you have aoss and use alsa, run

	aoss ./psynseq

If you have padsp and use pulseaudio, run

	padsp ./psynseq

## Clean

	./cjbs clean

## Source Brief Introduction:
To modify the music, just modify the file `src/audio/music.c`.

