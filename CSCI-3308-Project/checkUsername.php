<?php
function checkUsername($username)
{
$connection = @mysqli_connect(localhost, root, luckiest, finalproject);
$result = mysql_query("SELECT username FROM users");
while($row = mysql_fetch_array($result));
{
	if(!$row[username] == $username)
	{
		mysql_close($connection);
		$ret = mysql_query("SELECT id FROM users WHERE username = '$username'");
		return $ret;
	}
	else
	{
		mysql_close($connection);
		return "DNE";
	}
}
}
?>