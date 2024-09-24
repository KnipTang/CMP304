using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using static RaceTrack;


/**
 * TrackSection controls a part of the RaceTrack displayed using the TrackSection prefab
 */
public class TrackSection : MonoBehaviour
{
   
    //information about this TrackSection
    public TrackSectionType trackSectionType;
    public bool isLegendLine = false;
    private int cornerSpeed = -1;
    public bool isStartLine = false;

    //links to the sprite components of the TrackSection
    public SpriteRenderer trackSprite;
    public SpriteRenderer speedLimitSprite;
    public SpriteRenderer legendSprite;
    public SpriteRenderer startSprite;
    public Sprite CornerSW;
    public Sprite CornerSE;
    public Sprite CornerNW;
    public Sprite CornerNE;
    public Sprite Straight;

    // the Speed Limit text shown on the TrackSection
    public TMPro.TextMeshPro speedLimit;


    void Start()
    {
        
    }

    void Update()
    {

    }

    public int getCornerSpeed()
    {
        return cornerSpeed;
    }

    /**
     * initTrackSection will confgiure the appearance and settings for the TrackSection
     */
    public void initTrackSection(TrackSectionType trackSectionType, bool isLegendLine, bool isStartLine)
    {
        this.isLegendLine = isLegendLine;
        this.trackSectionType = trackSectionType;
        this.isStartLine = isStartLine;

        //select the appropriate Sprite for the configuration, and ensure correct rotation
        if (trackSectionType == TrackSectionType.CornerSE)
            trackSprite.sprite = CornerSE;
        else if (trackSectionType == TrackSectionType.CornerSW)
            trackSprite.sprite = CornerSW;
        else if (trackSectionType == TrackSectionType.CornerNW)
            trackSprite.sprite = CornerNW;
        else if (trackSectionType == TrackSectionType.CornerNE)
            trackSprite.sprite = CornerNE;
        else if (trackSectionType == TrackSectionType.HorizontalWE)
        {
            this.transform.Rotate(new Vector3 (0, 0, -90));
            trackSprite.sprite = Straight;
        }
        else if (trackSectionType == TrackSectionType.HorizontalEW)
        {
            this.transform.Rotate(new Vector3(0, 0, 90));
            trackSprite.sprite = Straight;
        }
        else if (trackSectionType == TrackSectionType.VerticalSN)
        {
         
            trackSprite.sprite = Straight;
        }
        else if (trackSectionType == TrackSectionType.VerticalNS)
        {
            this.transform.Rotate(new Vector3(0, 0, 180));
            trackSprite.sprite = Straight;
        }
      

        // enable or disable the display of the TrackSection components

        if (isLegendLine)
            legendSprite.enabled = true;
        else
            legendSprite.enabled = false;

        if (isCorner())
        {
            speedLimitSprite.enabled = true;
            speedLimit.enabled = true;          
        }
        else
        {
            speedLimitSprite.enabled = false;
            speedLimit.enabled = false;
        }

        if(isStartLine)
            startSprite.enabled = true;
        else
            startSprite.enabled = false;
    }
   
    public void setCornerSpeed(int cornerSpeed)
    {
        if (cornerSpeed < 1 || cornerSpeed > 9)
        {
            Debug.LogWarning("WARNING: Trying to see invalid corner speed: " + cornerSpeed);
            return;
        }

        this.cornerSpeed = cornerSpeed;
        speedLimit.text = cornerSpeed.ToString();
    }

    public bool isCorner()
    {
        if(trackSectionType == RaceTrack.TrackSectionType.CornerNE || 
            trackSectionType == RaceTrack.TrackSectionType.CornerNW ||
            trackSectionType == RaceTrack.TrackSectionType.CornerSE || 
            trackSectionType == RaceTrack.TrackSectionType.CornerSW  )
            return true;
        else
            return false;
    }



}

