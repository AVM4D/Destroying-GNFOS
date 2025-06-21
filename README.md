![GitHub release (latest by date)](https://img.shields.io/github/v/release/AVM4D/Destroying-GNFOS)

# 🌌 Destroying GNFOS: A Galactic Showdown

Welcome, brave pilot!  
The galaxy is under siege, and the fate of the universe rests on your shoulders. Navigate your spaceship, dodge enemy fire, and eliminate alien invaders in this adrenaline-pumping interstellar arcade shooter.

Whether you're a casual gamer or a hardcore space cadet, **Destroying GNFOS** offers thrilling action, animated enemies, save/load gameplay, and a retro-inspired challenge.

---

## 🎮 Features

### 🚀 Smooth, Strategic Gameplay
- **Controls**: Move with `W`, `A`, `S`, `D` — shoot with `Spacebar`
- **Bullet Cap**: Fire up to 10 bullets at a time — aim wisely!
- **Two Difficulty Modes**:
  - *Easy Mode*: Aliens fire randomly
  - *Hard Mode*: Aliens aim directly at you

### 💾 Save & Continue Later
- Pause anytime, save game state, and continue later from the main menu

### 👾 Enemy Mechanics
- Aliens animate arms and legs after each shift
- Lose the game if:
  - Alien bullet hits your ship
  - Your ship stays in alien formation too long
  - Aliens reach the left edge

### 🛡️ Shield System
- Shields can absorb 5 total hits
- Once depleted, it’s up to your reflexes!

### 🏆 High Scores
- Keep track of your top 5 scores

---

## 🛠️ Installation & Setup

### 🔧 Folder Structure (original project):
```text
DestroyingGNFOS/
├── source/
│   └── main.cpp
├── header/
│   └── help.h
├── sound/
│   ├── background.wav
│   ├── explode.wav
│   ├── gameover.wav
│   ├── shoot.wav
│   └── win.wav
├── text/
│   ├── gamestate.txt
│   ├── highscore.txt
│   ├── savegame.txt
│   └── top_scores.txt
├── Destroying GNFOS.exe
```

### ▶️ How to Play

To run the game correctly:

1. Create a folder (e.g. `DestroyingGNFOS_Playable`)
2. Copy the following files into **one folder**:
   - `Destroying GNFOS.exe`
   - All `.wav` files (from `sound/`)
   - All `.txt` files (from `text/`)
3. Final folder should look like:
```text
DestroyingGNFOS_Playable/
├── Destroying GNFOS.exe
├── background.wav
├── explode.wav
├── gameover.wav
├── shoot.wav
├── win.wav
├── gamestate.txt
├── highscore.txt
├── savegame.txt
├── top_scores.txt
```
4. Double-click `Destroying GNFOS.exe` to launch the game.

> ⚠️ The game **may not work properly** if all audio and text files aren't placed in the same folder as the executable.

---

## 💡 Tips for Galactic Domination

- Use shields wisely — they can take 5 hits.
- Only 10 bullets allowed at once — aim carefully.
- Save your game often and return to it anytime.

---

## 👨‍🚀 Credits

**Developed by:**  
- Ahmad Mursaleen  

**Built With:**
- C++
- Classic Space Invaders inspiration

---

## 📦 Playable Build

> A pre-packaged ZIP build with all files is available in the **[Releases](https://github.com/AVM4D/Destroying-GNFOS/releases)** section.

Stay tuned, and enjoy saving the galaxy!
