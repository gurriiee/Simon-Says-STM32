# ENSE-352 SIMON Game

## Project Overview:
This project is a SIMON game implemented with LEDs and buttons. The game challenges players to memorize and replicate a sequence of lights within a limited time. It includes features for game progression, winning conditions, and failure handling, meeting all project requirements.

## How My Game Works:
The game is designed for 5 rounds, allowing users to test their memory and reflexes. Players must successfully follow the light sequence to progress through the rounds.

### Beginner Sequence:
- The game starts with a Knight Rider light sequence.  
- The sequence runs until the player presses a button, signaling the start of **Round 1**.

### Gameplay:
1. **Round 1** begins when the button is pressed.  
   - A light sequence is displayed on the LEDs.  
   - The player replicates the sequence by pressing the corresponding button.  
   - When the player presses a button, the corresponding LED lights up.  
   - The player has a limited time to press the correct button.
2. Upon success, the game advances to **Round 2**, adding another LED to the sequence.  
3. The game continues this pattern until **Round 5**.

### Game Won:
- If the player completes all 5 rounds successfully:  
  - All 4 LEDs blink on and off together 4 times as a "Game Won" sequence.  
  - The final level achieved is displayed as a 4-bit binary pattern on the LEDs.  
  - The pattern remains until the player presses a button to start a new game.

### Failure Sequence:
A failure occurs in one of the following scenarios:
1. The player enters the sequence incorrectly.  
2. The player fails to press the button in the allotted time.  

#### Failure Indication:
- Upon failure:
  - A specific LED sequence blinks 4 times to indicate the failure.  
  - The level achieved is displayed as a 4-bit binary pattern on the LEDs.  
  - The LEDs remain in this state until the player presses a button to restart the game.

## Features:
- **Interactive gameplay:** Progresses through 5 levels of increasing difficulty which can be increased or decreased.  
- **Visual feedback:** Uses LEDs for sequences, success, and failure indications.  
- **Customizable:** Time limits and failure sequences can be adjusted by the game designer.  
- **Meets Requirements:** Fully adheres to the project specifications.

## Future Iterations or Deficiencies
- I would like to introduce a change where players must memorize the LED sequence from previous rounds because those LEDs will no longer blink in subsequent rounds. For example:

1. At the start of the game, the LED sequence for Round 1 will blink.
2. In Round 2, only the new LED in the sequence will blink, while the LEDs from previous rounds remain unlit.
3. This change challenges players to retain the entire sequence in memory as they progress toward victory.

- Additionally, I would like to integrate a 7-segment display to enhance visual feedback by showing the current round number, the winning round upon success, and the failure round upon losing.

1. To achieve this, the design will incorporate two ICs:
A) 74HC166 (a shift register to input data for the 7-segment display).
B) 74HC164 (a parallel-to-serial shift register for controlling the display).
C) The setup will also include two resistors for proper circuit functionality.
D) This enhancement improves user experience by clearly displaying the game's progress and outcome.

## Instructions:
1. Start the game and wait for the Knight Rider sequence.  
2. Press any button to initiate **Round 1**.  
3. Replicate the light sequence displayed by the LEDs using the buttons.  
4. Continue through the rounds until you either win or fail.  
5. If you win, enjoy the "Game Won" sequence and restart by pressing any button.  
6. If you fail, view the failure sequence and restart by pressing any button.

## Conclusion:
The SIMON game provides an engaging memory challenge with clear success and failure feedback. The project fulfills all specified requirements and is customizable for further enhancements.
