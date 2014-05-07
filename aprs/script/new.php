<?

$url = "http://c.hiphotos.baidu.com/lvpics/w%3D300/sign=08942db4f2d3572c66e29adcba126352/b3508d13b23b85ed6538db97.jpg";
//$url = "http://b.hiphotos.baidu.com/lvpics/w%3D300/sign=fd02ab097bcb0a4685228d395b61f63e/902397dda144ad34a873ce74d0a20cf430ad8571.jpg";

$downfile = str_replace(" ", "%20", $url); 
$downfile = str_replace("http://", "", $downfile);
$urlarr = explode("/", $downfile);
$domain = $urlarr[0];
$getfile = str_replace($urlarr[0], '', $downfile);
$content = @fsockopen("$domain", 80, $errno, $errstr, 12);

if (!$content){
    die("对不起，无法连接上 $domain 。");
}

echo "GET $getfile HTTP/1.0\n";
echo "Host: $domain\n";
echo "Referer: $domain\n";
echo "User-Agent: Mozilla/4.0 (compatible; MSIE 6.0; Windows NT 5.1)\n\n";

fputs($content, "GET $getfile HTTP/1.0\n");
fputs($content, "Host: $domain\n");
fputs($content, "Referer: $domain\n");
fputs($content, "User-Agent: Mozilla/4.0 (compatible; MSIE 6.0; Windows NT 5.1)\n\n");
$tp = "";
while (!feof($content)) {
    echo fgets($content, 128);
}
die();
?>
