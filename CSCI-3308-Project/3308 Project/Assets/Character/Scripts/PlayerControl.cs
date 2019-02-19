using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.SceneManagement;
using UnityEngine.UI;

public class PlayerControl : MonoBehaviour {

	// The pausing script
	public PauseGame other;
	
	
	public Text countText;
	public int score;
	public int bonus;
	public float speed;
	public float jumpForce;
	public float speedIncreaseMilestone;
	public float speedMultiplier;
	private float speedMilestoneCount;
	private float startTime;
	public int merp;

	private Rigidbody2D myRigidbody;

	public bool grounded;
	public LayerMask whatIsGround;

	public bool touchingCoin;
	public LayerMask whatIsCoin;


	private Collider2D myCollider;

	private Animator myAnimator;

     private bool secondJumpAvail = false;

	// Use this for initialization
	void Start () {
		myRigidbody = GetComponent<Rigidbody2D>();

		myCollider = GetComponent<Collider2D>();

		myAnimator = GetComponent<Animator>();
		
		startTime = Time.time;
		
		score = 0;
		
		SetCountText();
		
		Time.timeScale = 1;
		
		
	}

	// Update is called once per frame
	void Update () {
		
		
		grounded = Physics2D.IsTouchingLayers(myCollider, whatIsGround);

		touchingCoin = Physics2D.IsTouchingLayers(myCollider, whatIsCoin);


if(transform.position.x > speedMilestoneCount){
	speedMilestoneCount += speedIncreaseMilestone;	
	
	speed = speed * speedMultiplier;

	speedIncreaseMilestone = speedIncreaseMilestone * speedMultiplier;
}
		myRigidbody.velocity = new Vector2(speed, myRigidbody.velocity.y);

        if (Input.GetKeyDown(KeyCode.Space))
        {
            if (grounded)
            {
                myRigidbody.velocity = new Vector2(myRigidbody.velocity.x, jumpForce);
                secondJumpAvail = true;
            }
            else
            {
                if (secondJumpAvail)
                {
                    myRigidbody.velocity = new Vector2(myRigidbody.velocity.x, jumpForce);
                    secondJumpAvail = false;
                }
            }
        }

        myAnimator.SetFloat("Speed", myRigidbody.velocity.x);
		myAnimator.SetBool("Grounded", grounded);

		Vector2 pPos = myRigidbody.position;
		float lowBound = -7;

		score = (int)(Time.time - startTime);
		if(touchingCoin){
			bonus += 100;
		}

		SetCountText();

		if (pPos.y<lowBound) {
			other.gOver(score);
		}
		


		}
	
	void SetCountText()
	{
		countText.text = "Score: " + score.ToString();

	}
	
	public int getScore()
	{
		return score;
	}
}

