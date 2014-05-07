<?php

    $con = mysql_connect("localhost","root","root");
    if (!$con)
    {
        die('Could not connect: ' . mysql_error());
    }

    mysql_select_db("aprs_test", $con);

    $result = mysql_query("SELECT ID, IMAGE_PATH_SOURCE FROM TRAVEL_INFO WHERE IMAGE_PATH = ''");

    while ($row = mysql_fetch_array($result)) {
        $id = $row['ID'];
        $file = httpcopy($row['IMAGE_PATH_SOURCE']);
        $res = mysql_query("UPDATE TRAVEL_INFO SET IMAGE_PATH = '$file' WHERE ID = $id");
        echo "id: $id\n";
        echo "file: $file\n";
        echo "result: $res\n";
    }

    function httpcopy($url, $file = "", $timeout = 60) {

        $file = empty($file) ? pathinfo($url, PATHINFO_BASENAME) : $file;

        $dir = pathinfo($file, PATHINFO_DIRNAME);
        !is_dir($dir) && @mkdir($dir, 0755, true);
        $url = str_replace(" ", "%20", $url);

        if(function_exists('curl_init')) {
            $ch = curl_init();
            curl_setopt($ch, CURLOPT_URL, $url);
            curl_setopt($ch, CURLOPT_HTTPHEADER, "text/html,application/xhtml+xml,application/xml;q=0.9,*/*;q=0.8");
            curl_setopt($ch, CURLOPT_TIMEOUT, $timeout);
            curl_setopt($ch, CURLOPT_CONNECTIONTIMEOUT, $timeout);
            curl_setopt($ch, CURLOPT_HEADER, 0);
            curl_setopt($ch, CURLOPT_HTTPAUTH, CURLAUTH_BASIC);
            curl_setopt($ch, CURLOPT_FOLLOWLOCATION, 1);
            curl_setopt($ch, CURLOPT_FRESH_CONNECT, 1);
            curl_setopt($ch, CURLOPT_USERAGENT, "Mozilla/4.0 (compatible; MSIE 5.01; Windows NT 5.0)");
            curl_setopt($ch, CURLOPT_REFERER, "http://c.hiphotos.baidu.com/");
            curl_setopt($ch, CURLOPT_RETURNTRANSFER, 1); 
            curl_setopt($ch, CURLOPT_BINARYTRANSFER, 1);
            $temp = curl_exec($ch);
            if(@file_put_contents($file, $temp) && !curl_error($ch)) {
                return $file;
            } else {
                return false;
            }
        } else {
            $opts = array(
                "http"=>array(
                "method"=>"GET",
                "header"=>"",
                "timeout"=>$timeout)
            );
            $context = stream_context_create($opts);
            if(@copy($url, $file, $context)) {
                //$http_response_header
                return $file;
            } else {
                return false;
            }
        }
    }
?>
