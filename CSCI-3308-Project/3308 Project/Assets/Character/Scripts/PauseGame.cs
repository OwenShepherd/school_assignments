using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.SceneManagement;
using UnityEngine.UI;

public class PauseGame : MonoBehaviour {
	
	public Transform pausing;
	public Transform ending;
	public Transform userInput;
	public Transform highscores;
	public Text scoreText;
	public Text textUser;
	public Text textScore;
	private IEnumerator target;
	public PlayerControl plyr;
	public int userScore;
	public Text var1;
	public Text var2;
	public Text var3;
	public Text var4;
	public Text var5;
	
	

	private string user;
	public PauseGame pauser;
    private string secretKey = "mySecretKey"; // Edit this value and make sure it's the same as the one stored on the server
    public string addScoreURL = "https://csci3308game.000webhostapp.com/addscore.php?"; //be sure to add a ? to your url
    public string highscoreURL = "https://csci3308game.000webhostapp.com/display.php";
 


	void Start()
	{
		
		ending.gameObject.SetActive(false);
		pausing.gameObject.SetActive(false);
		userInput.gameObject.SetActive(false);
		highscores.gameObject.SetActive(false);
	}

	// Update is called once per frame
	void Update () {
		
		if (Input.GetKeyDown(KeyCode.Escape))
		{
			Pause();
		}
		
		
	}
	
	public void hScores()
	{
		StartCoroutine(GetScores());
		highscores.gameObject.SetActive(true);
	}
	
	public void Pause()
	{
				// Checks to see if the pause menu is open already
				if (pausing.gameObject.activeInHierarchy == false)
				{
					// Opens the pause menu and freezes time
					pausing.gameObject.SetActive(true);
					Time.timeScale = 0;
				}
				else
				{
					// Closes the pause menu and un-freezes time
					pausing.gameObject.SetActive(false);
					Time.timeScale = 1;
				}
	}
	
	public void pReset()
	{
		pausing.gameObject.SetActive(false);
		Time.timeScale = 1;
		SceneManager.LoadScene (SceneManager.GetActiveScene ().name);
	}
	
	public void gOver(int score)
	{
		SetCountText(score);
		ending.gameObject.SetActive(true);
		Time.timeScale = 0;
		
	}
	
	public void eReset()
	{
		ending.gameObject.SetActive(false);
		Time.timeScale = 1;
		SceneManager.LoadScene (SceneManager.GetActiveScene ().name);
	}
	
	public void saveScore()
	{
		userInput.gameObject.SetActive(true);
	}
	
	public void getInput(string userName)
	{
		user = userName;
		Debug.Log("You entered: " + userName);
		doneIn();
	}
	
	public void doneHigh()
	{
		highscores.gameObject.SetActive(false);
	}
	
	public void doneIn()
	{
			
	
			userInput.gameObject.SetActive(false);
			StartCoroutine(PostScores(user,userScore));
	}
	
	public void quitGame()
	{
		Application.Quit();
	}
	
	
	void SetCountText(int score)
	{	
		userScore = score;
		scoreText.text = "Final Score: " + score.ToString();
	}
	
	// remember to use StartCoroutine when calling this function!
    public IEnumerator PostScores(string name, int score)
    {
        string post_url = addScoreURL;
		
		// Adding the variables to our URL form
		WWWForm form = new WWWForm();
		form.AddField("name",name);
		form.AddField("score",score);
 
        // Post the URL to the site and create a download object to get the result.
        WWW hs_post = new WWW(post_url,form);
        yield return hs_post; // Wait until the download is done
 
        if (hs_post.error != null)
        {
            print("There was an error posting the high score: " + hs_post.error);
        }
    }
 
    // Get the scores from the MySQL DB to display in a GUIText.
    // remember to use StartCoroutine when calling this function!
    public IEnumerator GetScores()
    {
        WWW hs_get = new WWW(highscoreURL);
        yield return hs_get;
 
        if (hs_get.error != null)
        {
            print("There was an error getting the high score: " + hs_get.error);
        }
        else
        {
                 string data = hs_get.text;
				 
				 string[] strr= data.Split(";"[0]);        
				 var1.text = "1: " + strr[0]+ "s";
				 var2.text = "2: " + strr[1]+ "s";
				 var3.text = "3: " + strr[2]+ "s";
				 var4.text = "4: " + strr[3]+ "s";
				 var5.text = "5: " + strr[4]+ "s";
        }
    }
 
}
