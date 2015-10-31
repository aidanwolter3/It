#It
It - the editor that edits itself. It is awesome. It is completely configurable and customizable. In fact, all it can do is edit it. Open it -> Edit it -> Write it -> Repeat.

##Modes
* Command - normal mode that can accept commands without entering text
* Insert - edit text in the buffer

##Command Mode
* **o** - toggle the buffer between compile output and program code
* **i** - enter insert mode
* **w** - write the buffer as the new editor (compile)
* **s** - save the contents of the buffer to file `main.cpp`
* **h, j, k, l** - move the cursor left, down, up, and right (like in vim)

##Insert Mode
* **ESC** - exit into command mode
* **any other key** - insert the letter into the buffer
