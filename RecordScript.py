from pygame import midi as pgm
import pyautogui
import pynput
from pynput.keyboard import Key, Controller
import pyaudio
import wave
import os
import time
import random
import scipy.signal
import numpy


chunk = 2^14  # Record in chunks of 1024 samples
sample_format = pyaudio.paInt16  # 16 bits per sample
fs = 44100  # Record at 44100 samples per second
chunktime=float(chunk)/float(fs)
channels=1
seconds = 3
latency=0.235 #in s
samplestartchunk=int(latency/chunktime)


totalframes=seconds*fs
totalchunks=int((fs/chunk)*seconds)+samplestartchunk+2
halftotalchunks=int(totalchunks/2)-samplestartchunk

pgm.init()  #Start Midi Module
keyboard = Controller() #virtual keyboard controller

save_path = os.getcwd() + '\\Waves\\'
wav_path = 'C:\\Users\\Flitschi Beats\\Documents\\MASTER\\3. Semester\\Research Project\\Dataset\\AudioClips\\New\\'
rename_path = os.getcwd() + '\\Presets\\RandomTemp\\'



def rename(path):

    with os.scandir(path) as dirs:
        for entry in dirs:
            i=1
            filepath = os.path.join(path, entry.name)
            os.rename(filepath,entry.name + '.adv')
            i=i+1

def record(filename,p):
    player = pgm.Output(3,190,256)
    #player.set_instrument(0)
    frames = []  # Initialize array to store frames

    player.note_on(64, 127)

    stream = p.open(format=sample_format,channels=channels,rate=fs,
                    frames_per_buffer=chunk, input=True)

    # Store data in chunks for 3 seconds
    for i in range(0, totalchunks):
        data = stream.read(chunk)
        frames.append(data)
        if i == halftotalchunks:
            player.note_off(64, 127)

    # Stop and close the stream
    stream.stop_stream()
    stream.close()
    #delete player and close midi module
    del player
    return frames

def savewav(filename,frames,p):
    # Save the recorded data as a WAV file
    wf = wave.open(save_path+filename + '.wav', 'wb')
    wf.setnchannels(channels)
    wf.setsampwidth(p.get_sample_size(sample_format))
    wf.setframerate(fs)
    wf.writeframes(b''.join(frames[samplestartchunk:]))
    wf.close()

def autorecord(k,name): #k number of recordings
    #needs 15.5 gb total
    #per sample runtime = 3.8 sec
    i=1
    #Create player 101
#k is from 2 to 590
#j is 1 to 50

    time.sleep(5)
    while i<=k:
        #tic=time.time()
        p = pyaudio.PyAudio()  # Create an interface to PortAudio
        j = 2 + ((i-1)//50)
        filename='User' + str(j) + 'Aug' + str(i - 50*((i-1)//50))
        soundarray=record(filename,p)
        savewav(filename,soundarray,p)
        keyboard.press('n')
        keyboard.release('n')
        time.sleep(0.5)
        keyboard.press(Key.down)
        keyboard.release(Key.down)
        time.sleep(0.1)
        keyboard.press(Key.enter)
        keyboard.release(Key.enter)
        i=i+1
        p.terminate()
        del p
        time.sleep(0.5)
        #elapsedtime=time.time() -tic

    pgm.quit()




autorecord(29450,'Random')
#for i in range(p.get_device_count()):
#    print(p.get_device_info_by_index(i))

