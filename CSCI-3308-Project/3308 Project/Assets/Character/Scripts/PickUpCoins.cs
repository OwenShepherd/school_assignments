using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class PickUpCoins : MonoBehaviour {

	public int points;

	private PlayerControl scoreManager;

	// Use this for initialization
	void Start () {
		scoreManager = FindObjectOfType<PlayerControl>();

	}
	
	// Update is called once per frame
	void Update () {
		
	}

	void OnTriggerEnter2D(Collider2D other){
		if(other.gameObject.name == "Player"){
			scoreManager.score += points;
		}
	}
}
