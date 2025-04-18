<h2 align="center">BlockBoard</h2>

<p>BlockBoard is an application that gives you a random number and a random letter on your keyboard
After that, the keyboard and mouse are disabled(only 2 keys are not disabled — your combination)
So you need to press the combination of the letter and the number to end the loop and end the execution. 
</p>


----

> [!WARNING]  
> If you decide to test or modify,comment `line 29`:
> ```bash
>    void BlockMouseMs() {
>    while (ExitCount < 2) {
>        SetCursorPos(WindowX() / 2, WindowY() / 2); 
>        this_thread::sleep_for(chrono::milliseconds(2));
>    }
>}
> ```
