picotool reboot -f -u
timeout /t 2
picotool load Napoleon_Console.uf2
timeout /t 2
picotool reboot