using System.Collections;
using System.Collections.Generic;
using System.Linq;
using Unity.Collections.LowLevel.Unsafe;
using UnityEngine;



/**
 * RaceManager will control the overall Race and handle user input
 */
public class RaceManager : MonoBehaviour
{
    public enum LegendColours { Blue, Black, Red, Yellow, Green, White}; // the possible colours for the Legend car
    private static float TURN_TIME = 1.0f; // time between moves when in auto-play

    // status and tracking
    private bool isPlaying = false;
    private float turnCountdown = 0;
    private int currentLegendTrackIndex = 0;
    private int curLegendCardIndex = 0;


    public CardUI cardUI;// the Database UI manager
    public GameObject legendCarPrefab; // the prefab used for the Legend playing peice
    public RaceTrack raceTrack; // the race track manager
    private CarObject legendCar; // the created playing piece for the Legend car

    private List<LegendCard> allLegendCards = new List<LegendCard>(); // Legend cards to be used duing play

    // the AI system components
    private Database database = new Database();
    private RuleBasedSystemAI gameAI = new RuleBasedSystemAI();

    private static System.Random rng = new System.Random();

    private void Start()
    {
        //create the set of legends cards used in the game
        createLegendCards();
        shuffleLegendCards();

        //Instantiate and position the LegendCar to the starting position in the game world

        Vector3 startingPosition = raceTrack.getCarPosForTrackIndex(0); // index 0 is starting position
        GameObject go = Instantiate(legendCarPrefab, startingPosition, Quaternion.identity);
        legendCar = go.GetComponent<CarObject>();
        legendCar.turnCar(raceTrack.getCurrentTrackType(currentLegendTrackIndex));// align car for track position
        // initialise the database with starting values and refresh the UI
        updateDatabase();
        cardUI.updateTrackData(database.distToNextLegendLine, database.distToNextCorner, database.legendTrackIndex, database.nextCornerSpeed, database.distToSecondCorner);
        cardUI.UpdateCardUI(database.currentLegendCard);

    }

    // Update is called once per frame
    void Update()
    {
        if(isPlaying)// if in auto-play mode
        {
            turnCountdown -= Time.deltaTime;

            if(turnCountdown < 0)
            {
                nextTurn();
                turnCountdown = TURN_TIME;
            }

        }
    }


    /**
     * OnPlayPressed will start the auto-play mode for the game
     */
    public void OnPlayPressed()
    {       
        isPlaying = true;
        turnCountdown = TURN_TIME;
    }


    /**
     * OnNextTurnPressed will trigger the game to move to the next state 
     */
    public void OnNextTurnPressed()
    {
        nextTurn();
    }

    /**
     * nextTurn will perform the sequence of actions for a turn 
     * AI will be asked for a move distance
     * car will moved
     * next Legend card drawn
     */
    private void nextTurn()
    {
        // ask the AI how far car should move
        int moveDistance = gameAI.CheckRules(database);

        // move car to next postition
        if (moveDistance > 0)
        {
            
            if(currentLegendTrackIndex + moveDistance >= raceTrack.getTrackLength())
            {
                currentLegendTrackIndex = ( currentLegendTrackIndex + moveDistance ) % raceTrack.getTrackLength();
            }
            else
            {
                currentLegendTrackIndex += moveDistance;
            }
            legendCar.transform.position = raceTrack.getCarPosForTrackIndex(currentLegendTrackIndex); // get the world position for the current track index
            legendCar.turnCar(raceTrack.getCurrentTrackType(currentLegendTrackIndex));// align car for track position
        }
        else
        {
            Debug.LogWarning("WARNING: Car Move Distance <= 0 : " + moveDistance);
        }


        //update the database
        updateDatabase();

        // draw new card and update UI
        cardUI.UpdateCardUI(getNextLegendCard());
        cardUI.updateTrackData(database.distToNextLegendLine, database.distToNextCorner, database.legendTrackIndex, database.nextCornerSpeed, database.distToSecondCorner);

    }

    /**
     * updateDatabase will set the information stored in the database with the latest values  
     */
    private void updateDatabase()
    {
        database.currentLegendCard = allLegendCards[curLegendCardIndex];
        database.legendTrackIndex = currentLegendTrackIndex;
        database.distToNextLegendLine = raceTrack.getNextLegendLineDist(database.legendTrackIndex);
        (database.distToNextCorner , database.nextCornerSpeed) = raceTrack.getNextCornerData(database.legendTrackIndex);
        database.distToSecondCorner = raceTrack.getNextCornerSpeed(database.legendTrackIndex + database.distToNextCorner + 1) + database.distToNextCorner + 1;
   
    }

    /**
     * getNextLegendCard will draw the next legend card from the deck
     */
    public LegendCard getNextLegendCard()
    {
        curLegendCardIndex++;

        // if all cards used, shuffle deck and reset index
        if (curLegendCardIndex >= allLegendCards.Count)
        {
            curLegendCardIndex = 0;
            shuffleLegendCards();
        }

        return allLegendCards[curLegendCardIndex];
    }



    /**
     * shuffleLegendCards will randomly arrange all cards in the allLegendCards object
     */
    private void shuffleLegendCards()
    {
        allLegendCards = allLegendCards.OrderBy(_ => rng.Next()).ToList();
    }


    /**
     * createLegendCards will create a set of LegendCard using preset values
     */ 
    private void createLegendCards()
    {
        //card 0
        LegendCard card0 = new LegendCard(0);
        card0.addLegendValue(LegendColours.Red, 7, 2);
        card0.addLegendValue(LegendColours.Black, 7, 1);
        card0.addLegendValue(LegendColours.White, 8, 2);
        card0.addLegendValue(LegendColours.Blue, 6, 1);
        card0.addLegendValue(LegendColours.Yellow, 8, 2);
        card0.addLegendValue(LegendColours.Green, 9, 3);
        allLegendCards.Add(card0);

        //card 1
        LegendCard card1 = new LegendCard(1);
        card1.addLegendValue(LegendColours.Red, 8, 2);
        card1.addLegendValue(LegendColours.Black, 9, 3);
        card1.addLegendValue(LegendColours.White, 9, 3);
        card1.addLegendValue(LegendColours.Blue, 8, 2);
        card1.addLegendValue(LegendColours.Yellow, 6, 1);
        card1.addLegendValue(LegendColours.Green,6, 1);
        allLegendCards.Add(card1);

        //card 2
        LegendCard card2 = new LegendCard(2);
        card2.addLegendValue(LegendColours.Red, 6, 1);
        card2.addLegendValue(LegendColours.Black, 8, 1);
        card2.addLegendValue(LegendColours.White, 7, 1);
        card2.addLegendValue(LegendColours.Blue, 9, 2);
        card2.addLegendValue(LegendColours.Yellow, 5, 0);
        card2.addLegendValue(LegendColours.Green, 7, 2);
        allLegendCards.Add(card2);

        //card 3
        LegendCard card3 = new LegendCard(3);
        card3.addLegendValue(LegendColours.Red, 8, 2);
        card3.addLegendValue(LegendColours.Black, 5, 0);
        card3.addLegendValue(LegendColours.White, 8, 2);
        card3.addLegendValue(LegendColours.Blue, 7, 2);
        card3.addLegendValue(LegendColours.Yellow, 9, 3);
        card3.addLegendValue(LegendColours.Green, 5, 0);
        allLegendCards.Add(card3);

        //card 4
        LegendCard card4 = new LegendCard(4);
        card4.addLegendValue(LegendColours.Red, 9, 3);
        card4.addLegendValue(LegendColours.Black, 6, 1);
        card4.addLegendValue(LegendColours.White, 7, 2);
        card4.addLegendValue(LegendColours.Blue, 6, 1);
        card4.addLegendValue(LegendColours.Yellow, 5, 0);
        card4.addLegendValue(LegendColours.Green, 8 , 2);
        allLegendCards.Add(card4);

    }


}
