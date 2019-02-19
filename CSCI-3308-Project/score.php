<html>
	<head>
		<title> Track your highscores </title>
		<script src="https://ajax.googleapis.com/ajax/libs/jquery/3.1.1/jquery.min.js"></script>
	</head>
<body>
<form enctype="multipart/form-data" 
action="http://localhost/scoreInsertHandler.php">       
<p>username:&nbsp 
<input type="text" name="username" size="10" maxlength="25" /></p> 
<p>score:&nbsp   
<input type="text" name="score" size="10" maxlength="20" /></p>
<input type="submit" value="Insert Score" /> &nbsp
<input type="reset" />
</form>
</body>
</html>