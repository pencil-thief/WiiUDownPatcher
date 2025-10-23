Steps for use:  
Firstly, make sure you have CFW installed on your wiiu, if not look at the following guide; https://wiiu.hacks.guide/  

STEP 1: Delete the update data for the desired game (Main Menu -> settings -> Data Management -> Desired game and only delete the update data NOT THE BASE GAME!!!

STEP 2: Launch CFW  
STEP 3: Launch Homebrew Launcher  
STEP 4: Install the app "FTPiiU Everywhere" from the homebrew store  
STEP 5: On another device (Linux or Windows) install an FTP client - NOTE This is not an ftp client!!  
STEP 6: Launch "FTPiiU Everywhere" on your Wii U - Make a note of the displayed IP  
STEP 7: Conncet to the displayed IP via the FTP client on your PC  
STEP 8: Navigate to "storage_slc/security" and copy the "versions.bin" file to the PC - you can then close the FTP  
STEP 9: For the game you want to downpatch, locate the correct region and find the titleID - https://phunlabs.github.io/ (will be left-most number)  
STEP 10: Open the "DownPatcher.exe" and paste the titleID in the field  
STEP 11: locate and open the versions.bin file with the "open file button"  
STEP 12: Patch!!  
STEP 13: Re-establish the FTP using "FTPiiU Everywhere, and replace the file on your system with the newer, patched file  
Step 14: Enjoy! :)  

  
NOTE -- This code is probably very sloppy, i would've rather made it in python but wtv. THERE MAY BE IUSSUES - CONSOLE COULD BE BRICKED!!!!!! always double check the versions.bin and make the only chnaged are in the line of the titleID.  
Tested with Minecraft:WiiU edition - shoudl theoretically work with every downloadable game, would only reset disc games to base version - e.g. if your disc is version 1.1 you cant go to version 1.0 no matter what.
