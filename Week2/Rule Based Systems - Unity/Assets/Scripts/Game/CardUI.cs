using System.Collections;
using System.Collections.Generic;
using TMPro;
using UnityEngine;

/**
 * CardUI controls the information shown in the Database section of the UI
 */
public class CardUI : MonoBehaviour
{

    // links to each of the Text elemnets on the Card
    public TextMeshProUGUI yellowDiamond;
    public TextMeshProUGUI yellowSpeed;
    public TextMeshProUGUI redDiamond;
    public TextMeshProUGUI redSpeed;
    public TextMeshProUGUI blackDiamond;
    public TextMeshProUGUI blackSpeed;
    public TextMeshProUGUI whiteDiamond;
    public TextMeshProUGUI whiteSpeed;
    public TextMeshProUGUI greenDiamond;
    public TextMeshProUGUI greenSpeed;
    public TextMeshProUGUI blueDiamond;
    public TextMeshProUGUI blueSpeed;
    public TextMeshProUGUI legendLineDist;
    public TextMeshProUGUI cornerDist;
    public TextMeshProUGUI trackIndex;
    public TextMeshProUGUI cornerSpeed;
    public TextMeshProUGUI secondCornerDist;



    void Start()
    {
        
    }

    void Update()
    {
        
    }

    /**
     * UpdateCardUI will update the UI with values from the provided LegendCard
     */
    public void UpdateCardUI(LegendCard newCard)
    {
        yellowDiamond.text = newCard.getDiamondForColour(RaceManager.LegendColours.Yellow).ToString();
        redDiamond.text = newCard.getDiamondForColour(RaceManager.LegendColours.Red).ToString();
        blackDiamond.text = newCard.getDiamondForColour(RaceManager.LegendColours.Black).ToString();
        whiteDiamond.text = newCard.getDiamondForColour(RaceManager.LegendColours.White).ToString();
        greenDiamond.text = newCard.getDiamondForColour(RaceManager.LegendColours.Green).ToString();
        blueDiamond.text = newCard.getDiamondForColour(RaceManager.LegendColours.Blue).ToString();

        yellowSpeed.text = newCard.getSpeedForColour(RaceManager.LegendColours.Yellow).ToString();
        redSpeed.text = newCard.getSpeedForColour(RaceManager.LegendColours.Red).ToString();
        blackSpeed.text = newCard.getSpeedForColour(RaceManager.LegendColours.Black).ToString();
        whiteSpeed.text = newCard.getSpeedForColour(RaceManager.LegendColours.White).ToString();
        greenSpeed.text = newCard.getSpeedForColour(RaceManager.LegendColours.Green).ToString();
        blueSpeed.text = newCard.getSpeedForColour(RaceManager.LegendColours.Blue).ToString();

    }

    /**
     * updateTrackData will update the UI using the provided parameter values for the Corner, Legend Line and Track data
     */
    public void updateTrackData(int legendLineDist, int cornerDist, int trackIndex, int cornerSpeed, int secondCornerDist)
    {
        this.legendLineDist.text = legendLineDist.ToString();
        this.cornerDist.text = cornerDist.ToString();
        this.trackIndex.text = trackIndex.ToString();
        this.cornerSpeed.text = cornerSpeed.ToString();
        this.secondCornerDist.text = secondCornerDist.ToString();
    }
}
