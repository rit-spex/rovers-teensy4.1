### High-Power Simple Motor Controller G2 24v19

- Motor Driver Board: https://www.pololu.com/product/1367/resources
- Binary Command Reference: https://www.pololu.com/docs/0J77/6.2

### Pinout Diagram

![image](https://raw.githubusercontent.com/GlennTatum/rit-rovers/refs/heads/main/INTLLAB_PUMP/pump.png)

- Note either SCL pins will work on the `G2 24v19` of boards
- The SDA and SCL pins do not have pull-up resistors enabled, so you should make sure that your
master device has pull-ups on both lines, or add external ones yourself. If you find that you need to
add **<u>pull-up resistors</u>, a resistance of 10 kΩ** is a good place to start, but you might need to adjust the
resistance depending on how much capacitance is on the bus and how fast you want to run the clock
