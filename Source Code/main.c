#include "main.h"

static uint32_t randomSeed = 0;  // Global variable to hold the random seed

/* Constants *****************************************************************/
const int MAX_ROUNDS          = 5;        /* Set to 5+---------------------- rounds */
const int SCANNING_DELAY      = 500000;    /* Delay for beginning sequence */
const int DISPLAY_DELAY       = 5000000;   /* Delay when displaying sequence */
const int INTER_DISPLAY_DELAY = 500000;    /* Delay between LED flashes in sequence */
const int INPUT_TIMEOUT       = 3000000;   /* Timeout duration for user input */
const int BLINK_DELAY         = 500000;    /* Delay for blinking in Game Won sequence */

/* Function Prototypes ********************************************************/
void GPIO_Config(void);
void Delay(volatile uint32_t nCount);
void turnOnLED(int ledIndex);
void turnOffLED(int ledIndex);
void turnOffAllLEDs(void);
void turnOnAllLEDs(void);
bool isbuttonPressed(void);
int getButtonPressed(void);
void BeginningLEDsSequence(void);
bool PlayRound(int roundNumber, int sequence[]);
int generateRandomLED(void);
int getUserInput(volatile uint32_t timeout);
void WinningSequence(void);
void FailureSequence(int failedRound);
void displayFailedRoundinbinary(int round);
void displayLevelInBinary(int level);
void restartGame(void);
void seedRandomGeneration(void);

/* Main Function *************************************************************/
int main(void)
{
    GPIO_Config();

    while (1)
    {
        restartGame();
			
				

        BeginningLEDsSequence();
			
				seedRandomGeneration(); // Seed the random number generator

        

        // Generate a new sequence for the game
        int sequence[MAX_ROUNDS];
        for (int i = 0; i < MAX_ROUNDS; i++)
        {
            sequence[i] = generateRandomLED();
        }

        // Start the game rounds
        for (int round = 1; round <= MAX_ROUNDS; round++)
        {
            bool success = PlayRound(round, sequence);

            if (!success)
            {
                // Player failed, FailureSequence is called within PlayRound
                break; // Exit the round loop and start over
            }
            else if (round == MAX_ROUNDS)
            {
                // Player has completed all rounds successfully
                WinningSequence();
                break; // Exit the round loop and start over
            }
        }
    }
}

/* GPIO Configuration *******************************************************/
void GPIO_Config(void)
{
    /* Enable clock for AFIO */
    RCC->APB2ENR |= RCC_APB2ENR_AFIOEN;

    /* Enable clock for GPIOA and GPIOB */
    RCC->APB2ENR |= RCC_APB2ENR_IOPAEN; // Enable GPIOA clock
    RCC->APB2ENR |= RCC_APB2ENR_IOPBEN; // Enable GPIOB clock

    /* Configure LEDs as output push-pull at 50 MHz */

    /* Configure PA0 (LED0) */
    GPIOA->CRL &= ~((0xF) << (0 * 4)); // Clear mode and CNF bits for PA0
    GPIOA->CRL |= ((0x3) << (0 * 4));  // MODE0[1:0] = 0b11 (Output mode, 50 MHz)

    /* Configure PA1 (LED1) */
    GPIOA->CRL &= ~((0xF) << (1 * 4)); // Clear mode and CNF bits for PA1
    GPIOA->CRL |= ((0x3) << (1 * 4));  // MODE1[1:0] = 0b11

    /* Configure PA4 (LED2) */
    GPIOA->CRL &= ~((0xF) << (4 * 4)); // Clear mode and CNF bits for PA4
    GPIOA->CRL |= ((0x3) << (4 * 4));  // MODE4[1:0] = 0b11

    /* Configure PB0 (LED3) */
    GPIOB->CRL &= ~((0xF) << (0 * 4)); // Clear mode and CNF bits for PB0
    GPIOB->CRL |= ((0x3) << (0 * 4));  // MODE0[1:0] = 0b11

    /* Configure Buttons as input with pull-up */

    /* Configure PB4 (BUTTON0) */
    GPIOB->CRL &= ~((0xF) << (4 * 4)); // Clear mode and CNF bits for PB4
    GPIOB->CRL |= ((0x8) << (4 * 4));  // MODE4[1:0] = 0b00 (Input mode), CNF4[1:0] = 0b10

    /* Configure PB6 (BUTTON1) */
    GPIOB->CRL &= ~((0xF) << (6 * 4)); // Clear mode and CNF bits for PB6
    GPIOB->CRL |= ((0x8) << (6 * 4));  // MODE6[1:0] = 0b00, CNF6[1:0] = 0b10

    /* Configure PB8 (BUTTON2) */
    GPIOB->CRH &= ~((0xF) << ((8 - 8) * 4)); // Clear mode and CNF bits for PB8
    GPIOB->CRH |= ((0x8) << ((8 - 8) * 4));  // MODE8[1:0] = 0b00, CNF8[1:0] = 0b10

    /* Configure PB9 (BUTTON3) */
    GPIOB->CRH &= ~((0xF) << ((9 - 8) * 4)); // Clear mode and CNF bits for PB9
    GPIOB->CRH |= ((0x8) << ((9 - 8) * 4));  // MODE9[1:0] = 0b00, CNF9[1:0] = 0b10

    /* Enable pull-up resistors on buttons */
    GPIOB->ODR |= BTN_PIN_0 | BTN_PIN_1 | BTN_PIN_2 | BTN_PIN_3;
}

/* Delay Function *************************************************************/
void Delay(volatile uint32_t nCount)
{
    while (nCount--)
    {
        __asm("nop"); // Prevent optimization
    }
}

/* LED Control Functions *****************************************************/
void turnOnLED(int ledIndex)
{
    switch (ledIndex)
    {
    case 0:
        GPIOA->BSRR = LED_PIN_0;
        break;
    case 1:
        GPIOA->BSRR = LED_PIN_1;
        break;
    case 2:
        GPIOA->BSRR = LED_PIN_2;
        break;
    case 3:
        GPIOB->BSRR = LED_PIN_3;
        break;
    default:
        // Invalid LED index; optionally handle error
        break;
    }
}

void turnOffLED(int ledIndex)
{
    switch (ledIndex)
    {
    case 0:
        GPIOA->BRR = LED_PIN_0;
        break;
    case 1:
        GPIOA->BRR = LED_PIN_1;
        break;
    case 2:
        GPIOA->BRR = LED_PIN_2;
        break;
    case 3:
        GPIOB->BRR = LED_PIN_3;
        break;
    default:
        // Invalid LED index; optionally handle error
        break;
    }
}

void turnOffAllLEDs(void)
{
    GPIOA->BRR = LED_PIN_0 | LED_PIN_1 | LED_PIN_2;
    GPIOB->BRR = LED_PIN_3;
}

void turnOnAllLEDs(void)
{
    GPIOA->BSRR = LED_PIN_0 | LED_PIN_1 | LED_PIN_2;
    GPIOB->BSRR = LED_PIN_3;
}

/* Button Handling Functions *************************************************/
bool isbuttonPressed(void)
{
    // Read the IDR register once to avoid multiple hardware accesses
    uint32_t idr = GPIOB->IDR;

    if ((idr & BTN_PIN_0) == 0 ||
        (idr & BTN_PIN_1) == 0 ||
        (idr & BTN_PIN_2) == 0 ||
        (idr & BTN_PIN_3) == 0)
    {
        Delay(10000); // Debounce delay

        // Read the IDR register again after debounce delay
        idr = GPIOB->IDR;

        if ((idr & BTN_PIN_0) == 0 ||
            (idr & BTN_PIN_1) == 0 ||
            (idr & BTN_PIN_2) == 0 ||
            (idr & BTN_PIN_3) == 0)
        {
            return true;
        }
    }
    return false;
}

int getButtonPressed(void)
{
    // Read the IDR register once to avoid multiple hardware accesses
    uint32_t idr = GPIOB->IDR;

    if ((idr & BTN_PIN_0) == 0)
        return 0;
    if ((idr & BTN_PIN_1) == 0)
        return 1;
    if ((idr & BTN_PIN_2) == 0)
        return 2;
    if ((idr & BTN_PIN_3) == 0)
        return 3;
    return -1; // No button pressed
}

/* Beginning Sequence (Knight Rider/Cylon Eye Scanner) ***********************/
void BeginningLEDsSequence(void)
{
    int ledIndex = 0;
    int direction = 1; // 1 for forward, -1 for backward
    randomSeed = 0;    // Reset the random seed

    while (!isbuttonPressed())
    {
        turnOffAllLEDs();
        turnOnLED(ledIndex);
        Delay(SCANNING_DELAY);

        ledIndex += direction;

        if (ledIndex == 3)
            direction = -1;
        else if (ledIndex == 0)
            direction = 1;

        randomSeed++; // Increment seed to get a different value based on time
    }

    // Wait for button release
    while (isbuttonPressed())
        ;
}

/* Seed the Random Number Generator ******************************************/
void seedRandomGeneration(void)
{
    // Simple seeding mechanism using the value from BeginningSequence
    srand(randomSeed);
}

/* Generate a Random LED Index (0 to 3) *************************************/
int generateRandomLED(void)
{
    int NUMBER_OF_LEDS = 4;
    return rand() % NUMBER_OF_LEDS;
}

/* Get User Input with Timeout ***********************************************/
int getUserInput(volatile uint32_t timeout)
{
    while (timeout--)
    {
        int buttonIndex = getButtonPressed();
        if (buttonIndex != -1)
        {
            // Wait for button release
            while (getButtonPressed() != -1)
                ;

            return buttonIndex;
        }
    }
    return -1; // Timeout occurred
}

/* Play a Round of the Game **************************************************/
bool PlayRound(int roundNumber, int sequence[])
{
    int userResponse;
    bool success = true;

    // Ensure all LEDs are off before starting
    turnOffAllLEDs();

    // Display the sequence to the player
    for (int i = 0; i < roundNumber; i++)
    {
        turnOnLED(sequence[i]);
        Delay(DISPLAY_DELAY);
        turnOffLED(sequence[i]);
        Delay(INTER_DISPLAY_DELAY);
    }

    // Ensure all LEDs are off before user input
    turnOffAllLEDs();

    // User input phase
    for (int i = 0; i < roundNumber; i++)
    {
        userResponse = getUserInput(INPUT_TIMEOUT);

        if (userResponse == -1)
        {
            // Timeout occurred
            success = false;
            FailureSequence(roundNumber); // Pass the failed round number
            break;
        }
        else
        {
            // Light up the corresponding LED as feedback
            turnOnLED(userResponse);
            Delay(DISPLAY_DELAY / 2);
            turnOffLED(userResponse);
						Delay(DISPLAY_DELAY / 2);

            if (userResponse != sequence[i])
            {
                // Incorrect button pressed
                success = false;
                FailureSequence(roundNumber); // Pass the failed round number
                break;
            }
        }
    }

    return success;
}

/* Game Won Sequence *******************************************************/
void WinningSequence(void)
{
    // Blink all LEDs four times
    for (int i = 0; i < 4; i++)
    {
        turnOnAllLEDs();
        Delay(BLINK_DELAY);
        turnOffAllLEDs();
        Delay(BLINK_DELAY);
    }

    // Display level achieved (level 10)
    displayLevelInBinary(MAX_ROUNDS);

    // Wait for player to press any button
    while (!isbuttonPressed())
        ;

    // Wait for button release
    while (isbuttonPressed())
        ;
}

/* Failure Sequence with Failed Round Indication ****************************/
void FailureSequence(int failedRound)
{
    // Blink all LEDs rapidly to indicate failure
    for (int i = 0; i < 4; i++)
    {
				turnOnLED(1);
				turnOnLED(3);
        Delay(BLINK_DELAY / 2);
        turnOffAllLEDs();
        Delay(BLINK_DELAY / 2);
    }

    // Display the failed round number using LEDs
    displayFailedRoundinbinary(failedRound);

    // Wait for a brief moment before resetting
    Delay(DISPLAY_DELAY);
}

/* Display the Failed Round Number in Binary Using LEDs ********************/
void displayFailedRoundinbinary(int round)
{
    // Ensure the round number is within displayable range
    if (round < 1 || round > MAX_ROUNDS)
        round = MAX_ROUNDS; // Default to MAX_ROUNDS if out of range

    // Convert round number to binary and display using LEDs
    // LED0: LSB, LED3: MSB
    for (int bit = 0; bit < 4; bit++)
    {
        if (round & (1 << bit))
            turnOnLED(bit);
        else
            turnOffLED(bit);
    }

}

/* Display Level in Binary Using LEDs ****************************************/
void displayLevelInBinary(int level)
{
    turnOffAllLEDs();

    if (level & 0x1)
        turnOnLED(0);
    if (level & 0x2)
        turnOnLED(1);
    if (level & 0x4)
        turnOnLED(2);
    if (level & 0x8)
        turnOnLED(3);
}

/* Reset Game Variables and States ******************************************/
void restartGame(void)
{
    turnOffAllLEDs();
    // Reset any game variables if necessary
}
