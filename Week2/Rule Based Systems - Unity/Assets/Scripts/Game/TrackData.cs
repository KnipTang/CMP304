using System.Collections;
using System.Collections.Generic;
using UnityEngine;

/**
 * TrackData contains the data for c
 */
public class TrackData 
{

    public Vector3Int gridPos; // the position on the Grid where the track is placed
    public RaceTrack.TrackSectionType trackType; // the type of track (corner, straight etc)
    public int cornerSpeed; // the speed limit of the corner, -1 if none
    public bool legendLine; // if the track section has a legend line
    public bool startLine; // if the tract section is a starting line

    public TrackData()
    {

    }

    public TrackData(Vector3Int gridPos, RaceTrack.TrackSectionType trackType, int cornerSpeed = -1, bool legendLine = false, bool startLine = false)
    {
        this.gridPos = gridPos;
        this.trackType = trackType;
        this.cornerSpeed = cornerSpeed;
        this.legendLine = legendLine;
        this.startLine = startLine;
    }


}
