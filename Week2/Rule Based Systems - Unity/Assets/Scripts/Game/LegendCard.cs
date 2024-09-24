
using System.Collections.Generic;

using static RaceManager;

/**
 * LegendCard contains the inforation found on a Legend Card
 * 
 */
public class LegendCard 
{
    int cardID;
    //Each Legend Colour has an associated Speed and Diamond value shown in the card
    Dictionary<LegendColours, int> legendSpeed = new Dictionary<LegendColours, int>();
    Dictionary<LegendColours, int> legendDiamond = new Dictionary<LegendColours, int>();

    public LegendCard(int cardID)
    {
        this.cardID = cardID;
    }

    public void addLegendValue(LegendColours legendColour, int speed, int diamond )
    {
        legendSpeed.Add(legendColour, speed);
        legendDiamond.Add(legendColour, diamond);
    }

    public int getSpeedForColour(LegendColours legendColour)
    {
        return legendSpeed[legendColour];
    }

    public int getDiamondForColour(LegendColours legendColour)
    {
        return legendDiamond[legendColour];
    }
}

