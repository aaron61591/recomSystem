<?php

    $type = 1;

    $con = mysql_connect("localhost","root","root");
    if (!$con)
    {
        die('Could not connect: ' . mysql_error());
    }

    mysql_select_db("aprs_test", $con);

    switch ($type) {
        case 0:
            //for ($i = 1; $i < 944; ++$i) {
            for ($i = 1; $i < 6; ++$i) {
                $username = "yang" . $i;
                $mail = $username . "@163.com";
                $password = $username;
                $status = 1;
                $query = "INSERT INTO USER (ID, MAIL, USER_NAME, PASSWORD, STATUS) VALUES ($i, '$mail', '$username', '$password', '$status')";
                $result = mysql_query($query);
//                echo $query . "\nresult:" . $result . "\n";
            }
        break;
        case 1:
            //for ($i = 1; $i < 1683; ++$i) {
            for ($i = 1; $i < 6; ++$i) {
                $name = "name" . $i;
                $content = "content" . $i;
                $image = "image" . $i;
                $status = 1;
                $query = "INSERT INTO TRAVEL_INFO (ID, NAME, CONTENT, IMAGE_PATH, STATUS) VALUES ($i, '$name', '$content', '$image', '$status')";
                $result = mysql_query($query);
//                echo $query . "\nresult:" . $result . "\n";
            }
        break;
        case 2:
            $f = fopen("../data/u.data", "r");
            while (!feof($f)) {
                $line = fgets($f);
                $ele = preg_split('/[\s,;]+/',$line);
                $user = $ele[0];
                $pro = $ele[1];
                $point1 = $ele[2];
                $point2 = 0;
                $query = "INSERT INTO RECOM (USER_ID, PRO_ID, POINT1, POINT2) VALUES ('$user', '$pro', '$point1', '$point2')";
                $result = mysql_query($query);
//                echo $query . "\nresult:" . $result . "\n";
            }
        break;
    }
    mysql_close($con);
?>
