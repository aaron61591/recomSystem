<?php

$dir = '/home/aaron/Downloads/task';

$con = mysql_connect("localhost", "root", "root");
if (!$con) {
    die('could not connect!' . mysql_error());
}
mysql_select_db('aprs_test');
mysql_query("set names \"utf8\"");

if (is_dir($dir)) {
    if ($dh = opendir($dir)) {
        while (($file = readdir($dh)) != false) {
            if ($file != "." && $file != "..") {
                $f = fopen($dir . "/" . $file, "r");

                /* get content */
                $content = "";
                while (!feof($f)) {
                    $content .= fgets($f);
                }

                /* get signal content */
                $content = explode(',{"sid"', $content);

                $num = count($content);
                $i = 0;
                while ($i != $num){
                    $ele = "";
                    if ($i != 0)
                        $ele = '{"sid"' . $content[$i];

                    /* remove  \n \r */
                    $ele = str_replace("}\r\n", "}", $ele);
                    $ele = str_replace("\r\n", "<br/>", $ele);

                    /* get json object */
                    $ele = json_decode($ele);

                    /* insert into db */
                    $name = $ele->sname;
                    $con = $ele->desc;
                    $image = $ele->pic[0];
                    $status = 0;
                    if ($name != "" && $con != "" && $image != "") {
                        $query = "INSERT INTO TRAVEL_INFO (NAME, CONTENT, IMAGE_PATH, STATUS) VALUES ('$name', '$con', '$image', '$status')";
                        //$query = "INSERT INTO TRAVEL_INFO (NAME, CONTENT, IMAGE_PATH, STATUS) VALUES ('中文', '中文', '$image', '$status')";
                        mysql_query($query);
                        //echo $query . "\n";
                    } else {
                        echo "error json!" . "name:" . $name . ",con:" . $con . ",image:" . $image . "\n";
                    }

                    /* next */
                    ++$i;
                }
            }
        }
    }
    closedir($dh);
} else {
    echo "is not a dir\n";
}
?>
