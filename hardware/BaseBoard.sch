<?xml version="1.0" encoding="utf-8"?>
<!DOCTYPE eagle SYSTEM "eagle.dtd">
<eagle version="9.5.1">
<drawing>
<settings>
<setting alwaysvectorfont="no"/>
<setting verticaltext="up"/>
</settings>
<grid distance="0.1" unitdist="inch" unit="inch" style="lines" multiple="1" display="no" altdistance="0.01" altunitdist="inch" altunit="inch"/>
<layers>
<layer number="1" name="Top" color="4" fill="1" visible="no" active="no"/>
<layer number="2" name="Route2" color="16" fill="1" visible="no" active="no"/>
<layer number="3" name="Route3" color="17" fill="1" visible="no" active="no"/>
<layer number="4" name="Route4" color="18" fill="1" visible="no" active="no"/>
<layer number="5" name="Route5" color="19" fill="1" visible="no" active="no"/>
<layer number="6" name="Route6" color="25" fill="1" visible="no" active="no"/>
<layer number="7" name="Route7" color="26" fill="1" visible="no" active="no"/>
<layer number="8" name="Route8" color="27" fill="1" visible="no" active="no"/>
<layer number="9" name="Route9" color="28" fill="1" visible="no" active="no"/>
<layer number="10" name="Route10" color="29" fill="1" visible="no" active="no"/>
<layer number="11" name="Route11" color="30" fill="1" visible="no" active="no"/>
<layer number="12" name="Route12" color="20" fill="1" visible="no" active="no"/>
<layer number="13" name="Route13" color="21" fill="1" visible="no" active="no"/>
<layer number="14" name="Route14" color="22" fill="1" visible="no" active="no"/>
<layer number="15" name="Route15" color="23" fill="1" visible="no" active="no"/>
<layer number="16" name="Bottom" color="1" fill="1" visible="no" active="no"/>
<layer number="17" name="Pads" color="2" fill="1" visible="no" active="no"/>
<layer number="18" name="Vias" color="2" fill="1" visible="no" active="no"/>
<layer number="19" name="Unrouted" color="6" fill="1" visible="no" active="no"/>
<layer number="20" name="Dimension" color="15" fill="1" visible="no" active="no"/>
<layer number="21" name="tPlace" color="7" fill="1" visible="no" active="no"/>
<layer number="22" name="bPlace" color="7" fill="1" visible="no" active="no"/>
<layer number="23" name="tOrigins" color="15" fill="1" visible="no" active="no"/>
<layer number="24" name="bOrigins" color="15" fill="1" visible="no" active="no"/>
<layer number="25" name="tNames" color="7" fill="1" visible="no" active="no"/>
<layer number="26" name="bNames" color="7" fill="1" visible="no" active="no"/>
<layer number="27" name="tValues" color="7" fill="1" visible="no" active="no"/>
<layer number="28" name="bValues" color="7" fill="1" visible="no" active="no"/>
<layer number="29" name="tStop" color="7" fill="3" visible="no" active="no"/>
<layer number="30" name="bStop" color="7" fill="6" visible="no" active="no"/>
<layer number="31" name="tCream" color="7" fill="4" visible="no" active="no"/>
<layer number="32" name="bCream" color="7" fill="5" visible="no" active="no"/>
<layer number="33" name="tFinish" color="6" fill="3" visible="no" active="no"/>
<layer number="34" name="bFinish" color="6" fill="6" visible="no" active="no"/>
<layer number="35" name="tGlue" color="7" fill="4" visible="no" active="no"/>
<layer number="36" name="bGlue" color="7" fill="5" visible="no" active="no"/>
<layer number="37" name="tTest" color="7" fill="1" visible="no" active="no"/>
<layer number="38" name="bTest" color="7" fill="1" visible="no" active="no"/>
<layer number="39" name="tKeepout" color="4" fill="11" visible="no" active="no"/>
<layer number="40" name="bKeepout" color="1" fill="11" visible="no" active="no"/>
<layer number="41" name="tRestrict" color="4" fill="10" visible="no" active="no"/>
<layer number="42" name="bRestrict" color="1" fill="10" visible="no" active="no"/>
<layer number="43" name="vRestrict" color="2" fill="10" visible="no" active="no"/>
<layer number="44" name="Drills" color="7" fill="1" visible="no" active="no"/>
<layer number="45" name="Holes" color="7" fill="1" visible="no" active="no"/>
<layer number="46" name="Milling" color="3" fill="1" visible="no" active="no"/>
<layer number="47" name="Measures" color="7" fill="1" visible="no" active="no"/>
<layer number="48" name="Document" color="7" fill="1" visible="no" active="no"/>
<layer number="49" name="Reference" color="7" fill="1" visible="no" active="no"/>
<layer number="51" name="tDocu" color="7" fill="1" visible="no" active="no"/>
<layer number="52" name="bDocu" color="7" fill="1" visible="no" active="no"/>
<layer number="88" name="SimResults" color="9" fill="1" visible="yes" active="yes"/>
<layer number="89" name="SimProbes" color="9" fill="1" visible="yes" active="yes"/>
<layer number="90" name="Modules" color="5" fill="1" visible="yes" active="yes"/>
<layer number="91" name="Nets" color="2" fill="1" visible="yes" active="yes"/>
<layer number="92" name="Busses" color="1" fill="1" visible="yes" active="yes"/>
<layer number="93" name="Pins" color="2" fill="1" visible="no" active="yes"/>
<layer number="94" name="Symbols" color="4" fill="1" visible="yes" active="yes"/>
<layer number="95" name="Names" color="7" fill="1" visible="yes" active="yes"/>
<layer number="96" name="Values" color="7" fill="1" visible="yes" active="yes"/>
<layer number="97" name="Info" color="7" fill="1" visible="yes" active="yes"/>
<layer number="98" name="Guide" color="6" fill="1" visible="yes" active="yes"/>
</layers>
<schematic xreflabel="%F%N/%S.%C%R" xrefpart="/%S.%C%R">
<libraries>
<library name="con-pci_express(pci-e)">
<description>PCI-Express 16x  connectors, 164 contacts  (2*82)
Included: Trough-hole connector and edge-card pattern

Manufacturer: FCI  Reference: 10018783-10113TLF

Reference Radiospares: 615-9530 
Reference Digikey: 609-1975-ND</description>
<packages>
<package name="PCI-E_164_DATA_EDGE">
<wire x1="0" y1="8.4" x2="0" y2="0.5" width="0" layer="20"/>
<wire x1="0" y1="0.5" x2="0.5" y2="0" width="0" layer="20"/>
<wire x1="71.1" y1="8.4" x2="71.1" y2="0.5" width="0" layer="20"/>
<wire x1="71.1" y1="0.5" x2="70.6" y2="0" width="0" layer="20"/>
<wire x1="0.5" y1="0" x2="70.6" y2="0" width="0" layer="20"/>
<smd name="B12" x="0.55" y="3.7" dx="4" dy="0.7" layer="1" roundness="40" rot="R90"/>
<smd name="B13" x="1.55" y="3.7" dx="4" dy="0.7" layer="1" roundness="40" rot="R90"/>
<smd name="B14" x="2.55" y="3.7" dx="4" dy="0.7" layer="1" roundness="40" rot="R90"/>
<smd name="B15" x="3.55" y="3.7" dx="4" dy="0.7" layer="1" roundness="40" rot="R90"/>
<smd name="B16" x="4.55" y="3.7" dx="4" dy="0.7" layer="1" roundness="40" rot="R90"/>
<smd name="B17" x="5.55" y="3.7" dx="4" dy="0.7" layer="1" roundness="40" rot="R90"/>
<smd name="B18" x="6.55" y="3.7" dx="4" dy="0.7" layer="1" roundness="40" rot="R90"/>
<smd name="B19" x="7.55" y="3.7" dx="4" dy="0.7" layer="1" roundness="40" rot="R90"/>
<smd name="B20" x="8.55" y="3.7" dx="4" dy="0.7" layer="1" roundness="40" rot="R90"/>
<smd name="B21" x="9.55" y="3.7" dx="4" dy="0.7" layer="1" roundness="40" rot="R90"/>
<smd name="B22" x="10.55" y="3.7" dx="4" dy="0.7" layer="1" roundness="40" rot="R90"/>
<smd name="B23" x="11.55" y="3.7" dx="4" dy="0.7" layer="1" roundness="40" rot="R90"/>
<smd name="B24" x="12.55" y="3.7" dx="4" dy="0.7" layer="1" roundness="40" rot="R90"/>
<smd name="B25" x="13.55" y="3.7" dx="4" dy="0.7" layer="1" roundness="40" rot="R90"/>
<smd name="B26" x="14.55" y="3.7" dx="4" dy="0.7" layer="1" roundness="40" rot="R90"/>
<smd name="B27" x="15.55" y="3.7" dx="4" dy="0.7" layer="1" roundness="40" rot="R90"/>
<smd name="B28" x="16.55" y="3.7" dx="4" dy="0.7" layer="1" roundness="40" rot="R90"/>
<smd name="B29" x="17.55" y="3.7" dx="4" dy="0.7" layer="1" roundness="40" rot="R90"/>
<smd name="B30" x="18.55" y="3.7" dx="4" dy="0.7" layer="1" roundness="40" rot="R90"/>
<smd name="B31" x="19.55" y="3.7" dx="4" dy="0.7" layer="1" roundness="40" rot="R90"/>
<smd name="B32" x="20.55" y="3.7" dx="4" dy="0.7" layer="1" roundness="40" rot="R90"/>
<smd name="B33" x="21.55" y="3.7" dx="4" dy="0.7" layer="1" roundness="40" rot="R90"/>
<smd name="B34" x="22.55" y="3.7" dx="4" dy="0.7" layer="1" roundness="40" rot="R90"/>
<smd name="B35" x="23.55" y="3.7" dx="4" dy="0.7" layer="1" roundness="40" rot="R90"/>
<smd name="B36" x="24.55" y="3.7" dx="4" dy="0.7" layer="1" roundness="40" rot="R90"/>
<smd name="B37" x="25.55" y="3.7" dx="4" dy="0.7" layer="1" roundness="40" rot="R90"/>
<smd name="B38" x="26.55" y="3.7" dx="4" dy="0.7" layer="1" roundness="40" rot="R90"/>
<smd name="B39" x="27.55" y="3.7" dx="4" dy="0.7" layer="1" roundness="40" rot="R90"/>
<smd name="B40" x="28.55" y="3.7" dx="4" dy="0.7" layer="1" roundness="40" rot="R90"/>
<smd name="B41" x="29.55" y="3.7" dx="4" dy="0.7" layer="1" roundness="40" rot="R90"/>
<smd name="B42" x="30.55" y="3.7" dx="4" dy="0.7" layer="1" roundness="40" rot="R90"/>
<smd name="B43" x="31.55" y="3.7" dx="4" dy="0.7" layer="1" roundness="40" rot="R90"/>
<smd name="B44" x="32.55" y="3.7" dx="4" dy="0.7" layer="1" roundness="40" rot="R90"/>
<smd name="B45" x="33.55" y="3.7" dx="4" dy="0.7" layer="1" roundness="40" rot="R90"/>
<smd name="B46" x="34.55" y="3.7" dx="4" dy="0.7" layer="1" roundness="40" rot="R90"/>
<smd name="B47" x="35.55" y="3.7" dx="4" dy="0.7" layer="1" roundness="40" rot="R90"/>
<smd name="B48" x="36.55" y="3.7" dx="4" dy="0.7" layer="1" roundness="40" rot="R90"/>
<smd name="B49" x="37.55" y="3.7" dx="4" dy="0.7" layer="1" roundness="40" rot="R90"/>
<smd name="B50" x="38.55" y="3.7" dx="4" dy="0.7" layer="1" roundness="40" rot="R90"/>
<smd name="B51" x="39.55" y="3.7" dx="4" dy="0.7" layer="1" roundness="40" rot="R90"/>
<smd name="B52" x="40.55" y="3.7" dx="4" dy="0.7" layer="1" roundness="40" rot="R90"/>
<smd name="B53" x="41.55" y="3.7" dx="4" dy="0.7" layer="1" roundness="40" rot="R90"/>
<smd name="B54" x="42.55" y="3.7" dx="4" dy="0.7" layer="1" roundness="40" rot="R90"/>
<smd name="B55" x="43.55" y="3.7" dx="4" dy="0.7" layer="1" roundness="40" rot="R90"/>
<smd name="B56" x="44.55" y="3.7" dx="4" dy="0.7" layer="1" roundness="40" rot="R90"/>
<smd name="B57" x="45.55" y="3.7" dx="4" dy="0.7" layer="1" roundness="40" rot="R90"/>
<smd name="B58" x="46.55" y="3.7" dx="4" dy="0.7" layer="1" roundness="40" rot="R90"/>
<smd name="B59" x="47.55" y="3.7" dx="4" dy="0.7" layer="1" roundness="40" rot="R90"/>
<smd name="B60" x="48.55" y="3.7" dx="4" dy="0.7" layer="1" roundness="40" rot="R90"/>
<smd name="B61" x="49.55" y="3.7" dx="4" dy="0.7" layer="1" roundness="40" rot="R90"/>
<smd name="B62" x="50.55" y="3.7" dx="4" dy="0.7" layer="1" roundness="40" rot="R90"/>
<smd name="B63" x="51.55" y="3.7" dx="4" dy="0.7" layer="1" roundness="40" rot="R90"/>
<smd name="B64" x="52.55" y="3.7" dx="4" dy="0.7" layer="1" roundness="40" rot="R90"/>
<smd name="B65" x="53.55" y="3.7" dx="4" dy="0.7" layer="1" roundness="40" rot="R90"/>
<smd name="B66" x="54.55" y="3.7" dx="4" dy="0.7" layer="1" roundness="40" rot="R90"/>
<smd name="B67" x="55.55" y="3.7" dx="4" dy="0.7" layer="1" roundness="40" rot="R90"/>
<smd name="B68" x="56.55" y="3.7" dx="4" dy="0.7" layer="1" roundness="40" rot="R90"/>
<smd name="B69" x="57.55" y="3.7" dx="4" dy="0.7" layer="1" roundness="40" rot="R90"/>
<smd name="B70" x="58.55" y="3.7" dx="4" dy="0.7" layer="1" roundness="40" rot="R90"/>
<smd name="B71" x="59.55" y="3.7" dx="4" dy="0.7" layer="1" roundness="40" rot="R90"/>
<smd name="B72" x="60.55" y="3.7" dx="4" dy="0.7" layer="1" roundness="40" rot="R90"/>
<smd name="B73" x="61.55" y="3.7" dx="4" dy="0.7" layer="1" roundness="40" rot="R90"/>
<smd name="B74" x="62.55" y="3.7" dx="4" dy="0.7" layer="1" roundness="40" rot="R90"/>
<smd name="B75" x="63.55" y="3.7" dx="4" dy="0.7" layer="1" roundness="40" rot="R90"/>
<smd name="B76" x="64.55" y="3.7" dx="4" dy="0.7" layer="1" roundness="40" rot="R90"/>
<smd name="B77" x="65.55" y="3.7" dx="4" dy="0.7" layer="1" roundness="40" rot="R90"/>
<smd name="B78" x="66.55" y="3.7" dx="4" dy="0.7" layer="1" roundness="40" rot="R90"/>
<smd name="B79" x="67.55" y="3.7" dx="4" dy="0.7" layer="1" roundness="40" rot="R90"/>
<smd name="B80" x="68.55" y="3.7" dx="4" dy="0.7" layer="1" roundness="40" rot="R90"/>
<smd name="B81" x="69.55" y="3.7" dx="4" dy="0.7" layer="1" roundness="40" rot="R90"/>
<smd name="B82" x="70.55" y="3.7" dx="4" dy="0.7" layer="1" roundness="40" rot="R90"/>
<smd name="A12" x="0.55" y="3.7" dx="4" dy="0.7" layer="16" roundness="40" rot="R90"/>
<smd name="A13" x="1.55" y="3.7" dx="4" dy="0.7" layer="16" roundness="40" rot="R90"/>
<smd name="A14" x="2.55" y="3.7" dx="4" dy="0.7" layer="16" roundness="40" rot="R90"/>
<smd name="A15" x="3.55" y="3.7" dx="4" dy="0.7" layer="16" roundness="40" rot="R90"/>
<smd name="A16" x="4.55" y="3.7" dx="4" dy="0.7" layer="16" roundness="40" rot="R90"/>
<smd name="A17" x="5.55" y="3.7" dx="4" dy="0.7" layer="16" roundness="40" rot="R90"/>
<smd name="A18" x="6.55" y="3.7" dx="4" dy="0.7" layer="16" roundness="40" rot="R90"/>
<smd name="A19" x="7.55" y="3.7" dx="4" dy="0.7" layer="16" roundness="40" rot="R90"/>
<smd name="A20" x="8.55" y="3.7" dx="4" dy="0.7" layer="16" roundness="40" rot="R90"/>
<smd name="A21" x="9.55" y="3.7" dx="4" dy="0.7" layer="16" roundness="40" rot="R90"/>
<smd name="A22" x="10.55" y="3.7" dx="4" dy="0.7" layer="16" roundness="40" rot="R90"/>
<smd name="A23" x="11.55" y="3.7" dx="4" dy="0.7" layer="16" roundness="40" rot="R90"/>
<smd name="A24" x="12.55" y="3.7" dx="4" dy="0.7" layer="16" roundness="40" rot="R90"/>
<smd name="A25" x="13.55" y="3.7" dx="4" dy="0.7" layer="16" roundness="40" rot="R90"/>
<smd name="A26" x="14.55" y="3.7" dx="4" dy="0.7" layer="16" roundness="40" rot="R90"/>
<smd name="A27" x="15.55" y="3.7" dx="4" dy="0.7" layer="16" roundness="40" rot="R90"/>
<smd name="A28" x="16.55" y="3.7" dx="4" dy="0.7" layer="16" roundness="40" rot="R90"/>
<smd name="A29" x="17.55" y="3.7" dx="4" dy="0.7" layer="16" roundness="40" rot="R90"/>
<smd name="A30" x="18.55" y="3.7" dx="4" dy="0.7" layer="16" roundness="40" rot="R90"/>
<smd name="A31" x="19.55" y="3.7" dx="4" dy="0.7" layer="16" roundness="40" rot="R90"/>
<smd name="A32" x="20.55" y="3.7" dx="4" dy="0.7" layer="16" roundness="40" rot="R90"/>
<smd name="A33" x="21.55" y="3.7" dx="4" dy="0.7" layer="16" roundness="40" rot="R90"/>
<smd name="A34" x="22.55" y="3.7" dx="4" dy="0.7" layer="16" roundness="40" rot="R90"/>
<smd name="A35" x="23.55" y="3.7" dx="4" dy="0.7" layer="16" roundness="40" rot="R90"/>
<smd name="A36" x="24.55" y="3.7" dx="4" dy="0.7" layer="16" roundness="40" rot="R90"/>
<smd name="A37" x="25.55" y="3.7" dx="4" dy="0.7" layer="16" roundness="40" rot="R90"/>
<smd name="A38" x="26.55" y="3.7" dx="4" dy="0.7" layer="16" roundness="40" rot="R90"/>
<smd name="A39" x="27.55" y="3.7" dx="4" dy="0.7" layer="16" roundness="40" rot="R90"/>
<smd name="A40" x="28.55" y="3.7" dx="4" dy="0.7" layer="16" roundness="40" rot="R90"/>
<smd name="A41" x="29.55" y="3.7" dx="4" dy="0.7" layer="16" roundness="40" rot="R90"/>
<smd name="A42" x="30.55" y="3.7" dx="4" dy="0.7" layer="16" roundness="40" rot="R90"/>
<smd name="A43" x="31.55" y="3.7" dx="4" dy="0.7" layer="16" roundness="40" rot="R90"/>
<smd name="A44" x="32.55" y="3.7" dx="4" dy="0.7" layer="16" roundness="40" rot="R90"/>
<smd name="A45" x="33.55" y="3.7" dx="4" dy="0.7" layer="16" roundness="40" rot="R90"/>
<smd name="A46" x="34.55" y="3.7" dx="4" dy="0.7" layer="16" roundness="40" rot="R90"/>
<smd name="A47" x="35.55" y="3.7" dx="4" dy="0.7" layer="16" roundness="40" rot="R90"/>
<smd name="A48" x="36.55" y="3.7" dx="4" dy="0.7" layer="16" roundness="40" rot="R90"/>
<smd name="A49" x="37.55" y="3.7" dx="4" dy="0.7" layer="16" roundness="40" rot="R90"/>
<smd name="A50" x="38.55" y="3.7" dx="4" dy="0.7" layer="16" roundness="40" rot="R90"/>
<smd name="A51" x="39.55" y="3.7" dx="4" dy="0.7" layer="16" roundness="40" rot="R90"/>
<smd name="A52" x="40.55" y="3.7" dx="4" dy="0.7" layer="16" roundness="40" rot="R90"/>
<smd name="A53" x="41.55" y="3.7" dx="4" dy="0.7" layer="16" roundness="40" rot="R90"/>
<smd name="A54" x="42.55" y="3.7" dx="4" dy="0.7" layer="16" roundness="40" rot="R90"/>
<smd name="A55" x="43.55" y="3.7" dx="4" dy="0.7" layer="16" roundness="40" rot="R90"/>
<smd name="A56" x="44.55" y="3.7" dx="4" dy="0.7" layer="16" roundness="40" rot="R90"/>
<smd name="A57" x="45.55" y="3.7" dx="4" dy="0.7" layer="16" roundness="40" rot="R90"/>
<smd name="A58" x="46.55" y="3.7" dx="4" dy="0.7" layer="16" roundness="40" rot="R90"/>
<smd name="A59" x="47.55" y="3.7" dx="4" dy="0.7" layer="16" roundness="40" rot="R90"/>
<smd name="A60" x="48.55" y="3.7" dx="4" dy="0.7" layer="16" roundness="40" rot="R90"/>
<smd name="A61" x="49.55" y="3.7" dx="4" dy="0.7" layer="16" roundness="40" rot="R90"/>
<smd name="A62" x="50.55" y="3.7" dx="4" dy="0.7" layer="16" roundness="40" rot="R90"/>
<smd name="A63" x="51.55" y="3.7" dx="4" dy="0.7" layer="16" roundness="40" rot="R90"/>
<smd name="A64" x="52.55" y="3.7" dx="4" dy="0.7" layer="16" roundness="40" rot="R90"/>
<smd name="A65" x="53.55" y="3.7" dx="4" dy="0.7" layer="16" roundness="40" rot="R90"/>
<smd name="A66" x="54.55" y="3.7" dx="4" dy="0.7" layer="16" roundness="40" rot="R90"/>
<smd name="A67" x="55.55" y="3.7" dx="4" dy="0.7" layer="16" roundness="40" rot="R90"/>
<smd name="A68" x="56.55" y="3.7" dx="4" dy="0.7" layer="16" roundness="40" rot="R90"/>
<smd name="A69" x="57.55" y="3.7" dx="4" dy="0.7" layer="16" roundness="40" rot="R90"/>
<smd name="A70" x="58.55" y="3.7" dx="4" dy="0.7" layer="16" roundness="40" rot="R90"/>
<smd name="A71" x="59.55" y="3.7" dx="4" dy="0.7" layer="16" roundness="40" rot="R90"/>
<smd name="A72" x="60.55" y="3.7" dx="4" dy="0.7" layer="16" roundness="40" rot="R90"/>
<smd name="A73" x="61.55" y="3.7" dx="4" dy="0.7" layer="16" roundness="40" rot="R90"/>
<smd name="A74" x="62.55" y="3.7" dx="4" dy="0.7" layer="16" roundness="40" rot="R90"/>
<smd name="A75" x="63.55" y="3.7" dx="4" dy="0.7" layer="16" roundness="40" rot="R90"/>
<smd name="A76" x="64.55" y="3.7" dx="4" dy="0.7" layer="16" roundness="40" rot="R90"/>
<smd name="A77" x="65.55" y="3.7" dx="4" dy="0.7" layer="16" roundness="40" rot="R90"/>
<smd name="A78" x="66.55" y="3.7" dx="4" dy="0.7" layer="16" roundness="40" rot="R90"/>
<smd name="A79" x="67.55" y="3.7" dx="4" dy="0.7" layer="16" roundness="40" rot="R90"/>
<smd name="A80" x="68.55" y="3.7" dx="4" dy="0.7" layer="16" roundness="40" rot="R90"/>
<smd name="A81" x="69.55" y="3.7" dx="4" dy="0.7" layer="16" roundness="40" rot="R90"/>
<smd name="A82" x="70.55" y="3.7" dx="4" dy="0.7" layer="16" roundness="40" rot="R90"/>
</package>
</packages>
<symbols>
<symbol name="PCI-E_164_DATA">
<wire x1="-7.62" y1="86.36" x2="10.16" y2="86.36" width="0.254" layer="94"/>
<wire x1="10.16" y1="86.36" x2="10.16" y2="-96.52" width="0.254" layer="94"/>
<wire x1="10.16" y1="-96.52" x2="-7.62" y2="-96.52" width="0.254" layer="94"/>
<wire x1="-7.62" y1="-96.52" x2="-7.62" y2="86.36" width="0.254" layer="94"/>
<text x="2.54" y="-7.62" size="1.27" layer="95" rot="R90">&gt;NAME</text>
<text x="2.54" y="30.48" size="1.27" layer="96" rot="R90">&gt;VALUE</text>
<pin name="A12" x="-12.7" y="83.82" length="middle"/>
<pin name="A13" x="-12.7" y="81.28" length="middle"/>
<pin name="A14" x="-12.7" y="78.74" length="middle"/>
<pin name="A15" x="-12.7" y="76.2" length="middle"/>
<pin name="A16" x="-12.7" y="73.66" length="middle"/>
<pin name="A17" x="-12.7" y="71.12" length="middle"/>
<pin name="A18" x="-12.7" y="68.58" length="middle"/>
<pin name="A19" x="-12.7" y="66.04" length="middle"/>
<pin name="A20" x="-12.7" y="63.5" length="middle"/>
<pin name="A21" x="-12.7" y="60.96" length="middle"/>
<pin name="A22" x="-12.7" y="58.42" length="middle"/>
<pin name="A23" x="-12.7" y="55.88" length="middle"/>
<pin name="A24" x="-12.7" y="53.34" length="middle"/>
<pin name="A25" x="-12.7" y="50.8" length="middle"/>
<pin name="A26" x="-12.7" y="48.26" length="middle"/>
<pin name="A27" x="-12.7" y="45.72" length="middle"/>
<pin name="A28" x="-12.7" y="43.18" length="middle"/>
<pin name="A29" x="-12.7" y="40.64" length="middle"/>
<pin name="A30" x="-12.7" y="38.1" length="middle"/>
<pin name="A31" x="-12.7" y="35.56" length="middle"/>
<pin name="A32" x="-12.7" y="33.02" length="middle"/>
<pin name="A33" x="-12.7" y="30.48" length="middle"/>
<pin name="A34" x="-12.7" y="27.94" length="middle"/>
<pin name="A35" x="-12.7" y="25.4" length="middle"/>
<pin name="A36" x="-12.7" y="22.86" length="middle"/>
<pin name="A37" x="-12.7" y="20.32" length="middle"/>
<pin name="A38" x="-12.7" y="17.78" length="middle"/>
<pin name="A39" x="-12.7" y="15.24" length="middle"/>
<pin name="A40" x="-12.7" y="12.7" length="middle"/>
<pin name="A41" x="-12.7" y="10.16" length="middle"/>
<pin name="A42" x="-12.7" y="7.62" length="middle"/>
<pin name="A43" x="-12.7" y="5.08" length="middle"/>
<pin name="A44" x="-12.7" y="2.54" length="middle"/>
<pin name="A45" x="-12.7" y="0" length="middle"/>
<pin name="A46" x="-12.7" y="-2.54" length="middle"/>
<pin name="A47" x="-12.7" y="-5.08" length="middle"/>
<pin name="A48" x="-12.7" y="-7.62" length="middle"/>
<pin name="A49" x="-12.7" y="-10.16" length="middle"/>
<pin name="A50" x="-12.7" y="-12.7" length="middle"/>
<pin name="A51" x="-12.7" y="-15.24" length="middle"/>
<pin name="A52" x="-12.7" y="-17.78" length="middle"/>
<pin name="A53" x="-12.7" y="-20.32" length="middle"/>
<pin name="A54" x="-12.7" y="-22.86" length="middle"/>
<pin name="A55" x="-12.7" y="-25.4" length="middle"/>
<pin name="A56" x="-12.7" y="-27.94" length="middle"/>
<pin name="A57" x="-12.7" y="-30.48" length="middle"/>
<pin name="A58" x="-12.7" y="-33.02" length="middle"/>
<pin name="A59" x="-12.7" y="-35.56" length="middle"/>
<pin name="A60" x="-12.7" y="-38.1" length="middle"/>
<pin name="A61" x="-12.7" y="-40.64" length="middle"/>
<pin name="A62" x="-12.7" y="-43.18" length="middle"/>
<pin name="A63" x="-12.7" y="-45.72" length="middle"/>
<pin name="A64" x="-12.7" y="-48.26" length="middle"/>
<pin name="A65" x="-12.7" y="-50.8" length="middle"/>
<pin name="A66" x="-12.7" y="-53.34" length="middle"/>
<pin name="A67" x="-12.7" y="-55.88" length="middle"/>
<pin name="A68" x="-12.7" y="-58.42" length="middle"/>
<pin name="A69" x="-12.7" y="-60.96" length="middle"/>
<pin name="A70" x="-12.7" y="-63.5" length="middle"/>
<pin name="A71" x="-12.7" y="-66.04" length="middle"/>
<pin name="A72" x="-12.7" y="-68.58" length="middle"/>
<pin name="A73" x="-12.7" y="-71.12" length="middle"/>
<pin name="A74" x="-12.7" y="-73.66" length="middle"/>
<pin name="A75" x="-12.7" y="-76.2" length="middle"/>
<pin name="A76" x="-12.7" y="-78.74" length="middle"/>
<pin name="A77" x="-12.7" y="-81.28" length="middle"/>
<pin name="A78" x="-12.7" y="-83.82" length="middle"/>
<pin name="A79" x="-12.7" y="-86.36" length="middle"/>
<pin name="A80" x="-12.7" y="-88.9" length="middle"/>
<pin name="A81" x="-12.7" y="-91.44" length="middle"/>
<pin name="A82" x="-12.7" y="-93.98" length="middle"/>
<pin name="B12" x="15.24" y="83.82" length="middle" rot="R180"/>
<pin name="B13" x="15.24" y="81.28" length="middle" rot="R180"/>
<pin name="B14" x="15.24" y="78.74" length="middle" rot="R180"/>
<pin name="B15" x="15.24" y="76.2" length="middle" rot="R180"/>
<pin name="B16" x="15.24" y="73.66" length="middle" rot="R180"/>
<pin name="B17" x="15.24" y="71.12" length="middle" rot="R180"/>
<pin name="B18" x="15.24" y="68.58" length="middle" rot="R180"/>
<pin name="B19" x="15.24" y="66.04" length="middle" rot="R180"/>
<pin name="B20" x="15.24" y="63.5" length="middle" rot="R180"/>
<pin name="B21" x="15.24" y="60.96" length="middle" rot="R180"/>
<pin name="B22" x="15.24" y="58.42" length="middle" rot="R180"/>
<pin name="B23" x="15.24" y="55.88" length="middle" rot="R180"/>
<pin name="B24" x="15.24" y="53.34" length="middle" rot="R180"/>
<pin name="B25" x="15.24" y="50.8" length="middle" rot="R180"/>
<pin name="B26" x="15.24" y="48.26" length="middle" rot="R180"/>
<pin name="B27" x="15.24" y="45.72" length="middle" rot="R180"/>
<pin name="B28" x="15.24" y="43.18" length="middle" rot="R180"/>
<pin name="B29" x="15.24" y="40.64" length="middle" rot="R180"/>
<pin name="B30" x="15.24" y="38.1" length="middle" rot="R180"/>
<pin name="B31" x="15.24" y="35.56" length="middle" rot="R180"/>
<pin name="B32" x="15.24" y="33.02" length="middle" rot="R180"/>
<pin name="B33" x="15.24" y="30.48" length="middle" rot="R180"/>
<pin name="B34" x="15.24" y="27.94" length="middle" rot="R180"/>
<pin name="B35" x="15.24" y="25.4" length="middle" rot="R180"/>
<pin name="B36" x="15.24" y="22.86" length="middle" rot="R180"/>
<pin name="B37" x="15.24" y="20.32" length="middle" rot="R180"/>
<pin name="B38" x="15.24" y="17.78" length="middle" rot="R180"/>
<pin name="B39" x="15.24" y="15.24" length="middle" rot="R180"/>
<pin name="B40" x="15.24" y="12.7" length="middle" rot="R180"/>
<pin name="B41" x="15.24" y="10.16" length="middle" rot="R180"/>
<pin name="B42" x="15.24" y="7.62" length="middle" rot="R180"/>
<pin name="B43" x="15.24" y="5.08" length="middle" rot="R180"/>
<pin name="B44" x="15.24" y="2.54" length="middle" rot="R180"/>
<pin name="B45" x="15.24" y="0" length="middle" rot="R180"/>
<pin name="B46" x="15.24" y="-2.54" length="middle" rot="R180"/>
<pin name="B47" x="15.24" y="-5.08" length="middle" rot="R180"/>
<pin name="B48" x="15.24" y="-7.62" length="middle" rot="R180"/>
<pin name="B49" x="15.24" y="-10.16" length="middle" rot="R180"/>
<pin name="B50" x="15.24" y="-12.7" length="middle" rot="R180"/>
<pin name="B51" x="15.24" y="-15.24" length="middle" rot="R180"/>
<pin name="B52" x="15.24" y="-17.78" length="middle" rot="R180"/>
<pin name="B53" x="15.24" y="-20.32" length="middle" rot="R180"/>
<pin name="B54" x="15.24" y="-22.86" length="middle" rot="R180"/>
<pin name="B55" x="15.24" y="-25.4" length="middle" rot="R180"/>
<pin name="B56" x="15.24" y="-27.94" length="middle" rot="R180"/>
<pin name="B57" x="15.24" y="-30.48" length="middle" rot="R180"/>
<pin name="B58" x="15.24" y="-33.02" length="middle" rot="R180"/>
<pin name="B59" x="15.24" y="-35.56" length="middle" rot="R180"/>
<pin name="B60" x="15.24" y="-38.1" length="middle" rot="R180"/>
<pin name="B61" x="15.24" y="-40.64" length="middle" rot="R180"/>
<pin name="B62" x="15.24" y="-43.18" length="middle" rot="R180"/>
<pin name="B63" x="15.24" y="-45.72" length="middle" rot="R180"/>
<pin name="B64" x="15.24" y="-48.26" length="middle" rot="R180"/>
<pin name="B65" x="15.24" y="-50.8" length="middle" rot="R180"/>
<pin name="B66" x="15.24" y="-53.34" length="middle" rot="R180"/>
<pin name="B67" x="15.24" y="-55.88" length="middle" rot="R180"/>
<pin name="B68" x="15.24" y="-58.42" length="middle" rot="R180"/>
<pin name="B69" x="15.24" y="-60.96" length="middle" rot="R180"/>
<pin name="B70" x="15.24" y="-63.5" length="middle" rot="R180"/>
<pin name="B71" x="15.24" y="-66.04" length="middle" rot="R180"/>
<pin name="B72" x="15.24" y="-68.58" length="middle" rot="R180"/>
<pin name="B73" x="15.24" y="-71.12" length="middle" rot="R180"/>
<pin name="B74" x="15.24" y="-73.66" length="middle" rot="R180"/>
<pin name="B75" x="15.24" y="-76.2" length="middle" rot="R180"/>
<pin name="B76" x="15.24" y="-78.74" length="middle" rot="R180"/>
<pin name="B77" x="15.24" y="-81.28" length="middle" rot="R180"/>
<pin name="B78" x="15.24" y="-83.82" length="middle" rot="R180"/>
<pin name="B79" x="15.24" y="-86.36" length="middle" rot="R180"/>
<pin name="B80" x="15.24" y="-88.9" length="middle" rot="R180"/>
<pin name="B81" x="15.24" y="-91.44" length="middle" rot="R180"/>
<pin name="B82" x="15.24" y="-93.98" length="middle" rot="R180"/>
</symbol>
</symbols>
<devicesets>
<deviceset name="PCI-E16X_DATA_EDGE">
<gates>
<gate name="G$1" symbol="PCI-E_164_DATA" x="0" y="0"/>
</gates>
<devices>
<device name="" package="PCI-E_164_DATA_EDGE">
<connects>
<connect gate="G$1" pin="A12" pad="A12"/>
<connect gate="G$1" pin="A13" pad="A13"/>
<connect gate="G$1" pin="A14" pad="A14"/>
<connect gate="G$1" pin="A15" pad="A15"/>
<connect gate="G$1" pin="A16" pad="A16"/>
<connect gate="G$1" pin="A17" pad="A17"/>
<connect gate="G$1" pin="A18" pad="A18"/>
<connect gate="G$1" pin="A19" pad="A19"/>
<connect gate="G$1" pin="A20" pad="A20"/>
<connect gate="G$1" pin="A21" pad="A21"/>
<connect gate="G$1" pin="A22" pad="A22"/>
<connect gate="G$1" pin="A23" pad="A23"/>
<connect gate="G$1" pin="A24" pad="A24"/>
<connect gate="G$1" pin="A25" pad="A25"/>
<connect gate="G$1" pin="A26" pad="A26"/>
<connect gate="G$1" pin="A27" pad="A27"/>
<connect gate="G$1" pin="A28" pad="A28"/>
<connect gate="G$1" pin="A29" pad="A29"/>
<connect gate="G$1" pin="A30" pad="A30"/>
<connect gate="G$1" pin="A31" pad="A31"/>
<connect gate="G$1" pin="A32" pad="A32"/>
<connect gate="G$1" pin="A33" pad="A33"/>
<connect gate="G$1" pin="A34" pad="A34"/>
<connect gate="G$1" pin="A35" pad="A35"/>
<connect gate="G$1" pin="A36" pad="A36"/>
<connect gate="G$1" pin="A37" pad="A37"/>
<connect gate="G$1" pin="A38" pad="A38"/>
<connect gate="G$1" pin="A39" pad="A39"/>
<connect gate="G$1" pin="A40" pad="A40"/>
<connect gate="G$1" pin="A41" pad="A41"/>
<connect gate="G$1" pin="A42" pad="A42"/>
<connect gate="G$1" pin="A43" pad="A43"/>
<connect gate="G$1" pin="A44" pad="A44"/>
<connect gate="G$1" pin="A45" pad="A45"/>
<connect gate="G$1" pin="A46" pad="A46"/>
<connect gate="G$1" pin="A47" pad="A47"/>
<connect gate="G$1" pin="A48" pad="A48"/>
<connect gate="G$1" pin="A49" pad="A49"/>
<connect gate="G$1" pin="A50" pad="A50"/>
<connect gate="G$1" pin="A51" pad="A51"/>
<connect gate="G$1" pin="A52" pad="A52"/>
<connect gate="G$1" pin="A53" pad="A53"/>
<connect gate="G$1" pin="A54" pad="A54"/>
<connect gate="G$1" pin="A55" pad="A55"/>
<connect gate="G$1" pin="A56" pad="A56"/>
<connect gate="G$1" pin="A57" pad="A57"/>
<connect gate="G$1" pin="A58" pad="A58"/>
<connect gate="G$1" pin="A59" pad="A59"/>
<connect gate="G$1" pin="A60" pad="A60"/>
<connect gate="G$1" pin="A61" pad="A61"/>
<connect gate="G$1" pin="A62" pad="A62"/>
<connect gate="G$1" pin="A63" pad="A63"/>
<connect gate="G$1" pin="A64" pad="A64"/>
<connect gate="G$1" pin="A65" pad="A65"/>
<connect gate="G$1" pin="A66" pad="A66"/>
<connect gate="G$1" pin="A67" pad="A67"/>
<connect gate="G$1" pin="A68" pad="A68"/>
<connect gate="G$1" pin="A69" pad="A69"/>
<connect gate="G$1" pin="A70" pad="A70"/>
<connect gate="G$1" pin="A71" pad="A71"/>
<connect gate="G$1" pin="A72" pad="A72"/>
<connect gate="G$1" pin="A73" pad="A73"/>
<connect gate="G$1" pin="A74" pad="A74"/>
<connect gate="G$1" pin="A75" pad="A75"/>
<connect gate="G$1" pin="A76" pad="A76"/>
<connect gate="G$1" pin="A77" pad="A77"/>
<connect gate="G$1" pin="A78" pad="A78"/>
<connect gate="G$1" pin="A79" pad="A79"/>
<connect gate="G$1" pin="A80" pad="A80"/>
<connect gate="G$1" pin="A81" pad="A81"/>
<connect gate="G$1" pin="A82" pad="A82"/>
<connect gate="G$1" pin="B12" pad="B12"/>
<connect gate="G$1" pin="B13" pad="B13"/>
<connect gate="G$1" pin="B14" pad="B14"/>
<connect gate="G$1" pin="B15" pad="B15"/>
<connect gate="G$1" pin="B16" pad="B16"/>
<connect gate="G$1" pin="B17" pad="B17"/>
<connect gate="G$1" pin="B18" pad="B18"/>
<connect gate="G$1" pin="B19" pad="B19"/>
<connect gate="G$1" pin="B20" pad="B20"/>
<connect gate="G$1" pin="B21" pad="B21"/>
<connect gate="G$1" pin="B22" pad="B22"/>
<connect gate="G$1" pin="B23" pad="B23"/>
<connect gate="G$1" pin="B24" pad="B24"/>
<connect gate="G$1" pin="B25" pad="B25"/>
<connect gate="G$1" pin="B26" pad="B26"/>
<connect gate="G$1" pin="B27" pad="B27"/>
<connect gate="G$1" pin="B28" pad="B28"/>
<connect gate="G$1" pin="B29" pad="B29"/>
<connect gate="G$1" pin="B30" pad="B30"/>
<connect gate="G$1" pin="B31" pad="B31"/>
<connect gate="G$1" pin="B32" pad="B32"/>
<connect gate="G$1" pin="B33" pad="B33"/>
<connect gate="G$1" pin="B34" pad="B34"/>
<connect gate="G$1" pin="B35" pad="B35"/>
<connect gate="G$1" pin="B36" pad="B36"/>
<connect gate="G$1" pin="B37" pad="B37"/>
<connect gate="G$1" pin="B38" pad="B38"/>
<connect gate="G$1" pin="B39" pad="B39"/>
<connect gate="G$1" pin="B40" pad="B40"/>
<connect gate="G$1" pin="B41" pad="B41"/>
<connect gate="G$1" pin="B42" pad="B42"/>
<connect gate="G$1" pin="B43" pad="B43"/>
<connect gate="G$1" pin="B44" pad="B44"/>
<connect gate="G$1" pin="B45" pad="B45"/>
<connect gate="G$1" pin="B46" pad="B46"/>
<connect gate="G$1" pin="B47" pad="B47"/>
<connect gate="G$1" pin="B48" pad="B48"/>
<connect gate="G$1" pin="B49" pad="B49"/>
<connect gate="G$1" pin="B50" pad="B50"/>
<connect gate="G$1" pin="B51" pad="B51"/>
<connect gate="G$1" pin="B52" pad="B52"/>
<connect gate="G$1" pin="B53" pad="B53"/>
<connect gate="G$1" pin="B54" pad="B54"/>
<connect gate="G$1" pin="B55" pad="B55"/>
<connect gate="G$1" pin="B56" pad="B56"/>
<connect gate="G$1" pin="B57" pad="B57"/>
<connect gate="G$1" pin="B58" pad="B58"/>
<connect gate="G$1" pin="B59" pad="B59"/>
<connect gate="G$1" pin="B60" pad="B60"/>
<connect gate="G$1" pin="B61" pad="B61"/>
<connect gate="G$1" pin="B62" pad="B62"/>
<connect gate="G$1" pin="B63" pad="B63"/>
<connect gate="G$1" pin="B64" pad="B64"/>
<connect gate="G$1" pin="B65" pad="B65"/>
<connect gate="G$1" pin="B66" pad="B66"/>
<connect gate="G$1" pin="B67" pad="B67"/>
<connect gate="G$1" pin="B68" pad="B68"/>
<connect gate="G$1" pin="B69" pad="B69"/>
<connect gate="G$1" pin="B70" pad="B70"/>
<connect gate="G$1" pin="B71" pad="B71"/>
<connect gate="G$1" pin="B72" pad="B72"/>
<connect gate="G$1" pin="B73" pad="B73"/>
<connect gate="G$1" pin="B74" pad="B74"/>
<connect gate="G$1" pin="B75" pad="B75"/>
<connect gate="G$1" pin="B76" pad="B76"/>
<connect gate="G$1" pin="B77" pad="B77"/>
<connect gate="G$1" pin="B78" pad="B78"/>
<connect gate="G$1" pin="B79" pad="B79"/>
<connect gate="G$1" pin="B80" pad="B80"/>
<connect gate="G$1" pin="B81" pad="B81"/>
<connect gate="G$1" pin="B82" pad="B82"/>
</connects>
<technologies>
<technology name=""/>
</technologies>
</device>
</devices>
</deviceset>
</devicesets>
</library>
<library name="card_edge">
<packages>
<package name="CR22A-30D-2.54DS">
<pad name="P16" x="2.54" y="17.78" drill="0.8"/>
<pad name="P17" x="2.54" y="15.24" drill="0.8"/>
<pad name="P18" x="2.54" y="12.7" drill="0.8"/>
<pad name="P19" x="2.54" y="10.16" drill="0.8"/>
<pad name="P20" x="2.54" y="7.62" drill="0.8"/>
<pad name="P21" x="2.54" y="5.08" drill="0.8"/>
<pad name="P22" x="2.54" y="2.54" drill="0.8"/>
<pad name="P23" x="2.54" y="0" drill="0.8"/>
<pad name="P24" x="2.54" y="-2.54" drill="0.8"/>
<pad name="P25" x="2.54" y="-5.08" drill="0.8"/>
<pad name="P26" x="2.54" y="-7.62" drill="0.8"/>
<pad name="P27" x="2.54" y="-10.16" drill="0.8"/>
<pad name="P28" x="2.54" y="-12.7" drill="0.8"/>
<pad name="P29" x="2.54" y="-15.24" drill="0.8"/>
<pad name="P30" x="2.54" y="-17.78" drill="0.8"/>
<wire x1="-4.75" y1="23.37" x2="-4.75" y2="-23.37" width="0.127" layer="21"/>
<wire x1="-4.75" y1="-23.37" x2="4.75" y2="-23.37" width="0.127" layer="21"/>
<wire x1="4.75" y1="-23.37" x2="4.75" y2="23.37" width="0.127" layer="21"/>
<wire x1="4.75" y1="23.37" x2="-4.75" y2="23.37" width="0.127" layer="21"/>
<text x="-3.81" y="24.13" size="1.27" layer="25">&gt;NAME</text>
<text x="-3.81" y="-25.4" size="1.27" layer="27">&gt;VALUE</text>
<pad name="P1" x="-2.54" y="17.78" drill="0.8"/>
<pad name="P2" x="-2.54" y="15.24" drill="0.8"/>
<pad name="P3" x="-2.54" y="12.7" drill="0.8"/>
<pad name="P4" x="-2.54" y="10.16" drill="0.8"/>
<pad name="P5" x="-2.54" y="7.62" drill="0.8"/>
<pad name="P6" x="-2.54" y="5.08" drill="0.8"/>
<pad name="P7" x="-2.54" y="2.54" drill="0.8"/>
<pad name="P8" x="-2.54" y="0" drill="0.8"/>
<pad name="P9" x="-2.54" y="-2.54" drill="0.8"/>
<pad name="P10" x="-2.54" y="-5.08" drill="0.8"/>
<pad name="P11" x="-2.54" y="-7.62" drill="0.8"/>
<pad name="P12" x="-2.54" y="-10.16" drill="0.8"/>
<pad name="P13" x="-2.54" y="-12.7" drill="0.8"/>
<pad name="P14" x="-2.54" y="-15.24" drill="0.8"/>
<pad name="P15" x="-2.54" y="-17.78" drill="0.8"/>
</package>
</packages>
<symbols>
<symbol name="CR22*-30D">
<pin name="P1" x="5.08" y="38.1" length="middle" rot="R180"/>
<pin name="P2" x="5.08" y="35.56" length="middle" rot="R180"/>
<pin name="P3" x="5.08" y="33.02" length="middle" rot="R180"/>
<pin name="P4" x="5.08" y="30.48" length="middle" rot="R180"/>
<pin name="P5" x="5.08" y="27.94" length="middle" rot="R180"/>
<pin name="P6" x="5.08" y="25.4" length="middle" rot="R180"/>
<pin name="P7" x="5.08" y="22.86" length="middle" rot="R180"/>
<pin name="P8" x="5.08" y="20.32" length="middle" rot="R180"/>
<pin name="P9" x="5.08" y="17.78" length="middle" rot="R180"/>
<pin name="P10" x="5.08" y="15.24" length="middle" rot="R180"/>
<pin name="P11" x="5.08" y="12.7" length="middle" rot="R180"/>
<pin name="P12" x="5.08" y="10.16" length="middle" rot="R180"/>
<pin name="P13" x="5.08" y="7.62" length="middle" rot="R180"/>
<pin name="P14" x="5.08" y="5.08" length="middle" rot="R180"/>
<pin name="P15" x="5.08" y="2.54" length="middle" rot="R180"/>
<pin name="P16" x="5.08" y="0" length="middle" rot="R180"/>
<pin name="P17" x="5.08" y="-2.54" length="middle" rot="R180"/>
<pin name="P18" x="5.08" y="-5.08" length="middle" rot="R180"/>
<pin name="P19" x="5.08" y="-7.62" length="middle" rot="R180"/>
<pin name="P20" x="5.08" y="-10.16" length="middle" rot="R180"/>
<pin name="P21" x="5.08" y="-12.7" length="middle" rot="R180"/>
<pin name="P22" x="5.08" y="-15.24" length="middle" rot="R180"/>
<pin name="P23" x="5.08" y="-17.78" length="middle" rot="R180"/>
<pin name="P24" x="5.08" y="-20.32" length="middle" rot="R180"/>
<pin name="P25" x="5.08" y="-22.86" length="middle" rot="R180"/>
<pin name="P26" x="5.08" y="-25.4" length="middle" rot="R180"/>
<pin name="P27" x="5.08" y="-27.94" length="middle" rot="R180"/>
<pin name="P28" x="5.08" y="-30.48" length="middle" rot="R180"/>
<pin name="P29" x="5.08" y="-33.02" length="middle" rot="R180"/>
<pin name="P30" x="5.08" y="-35.56" length="middle" rot="R180"/>
<text x="-7.62" y="40.894" size="1.27" layer="95">&gt;NAME</text>
<text x="-7.62" y="-40.64" size="1.27" layer="96">&gt;VALUE</text>
<wire x1="0" y1="40.64" x2="0" y2="-38.1" width="0.254" layer="94"/>
<wire x1="0" y1="-38.1" x2="-7.62" y2="-38.1" width="0.254" layer="94"/>
<wire x1="-7.62" y1="-38.1" x2="-7.62" y2="40.64" width="0.254" layer="94"/>
<wire x1="-7.62" y1="40.64" x2="0" y2="40.64" width="0.254" layer="94"/>
</symbol>
</symbols>
<devicesets>
<deviceset name="CR22A-30D-2.54DS">
<gates>
<gate name="G$1" symbol="CR22*-30D" x="0" y="0"/>
</gates>
<devices>
<device name="" package="CR22A-30D-2.54DS">
<connects>
<connect gate="G$1" pin="P1" pad="P1"/>
<connect gate="G$1" pin="P10" pad="P10"/>
<connect gate="G$1" pin="P11" pad="P11"/>
<connect gate="G$1" pin="P12" pad="P12"/>
<connect gate="G$1" pin="P13" pad="P13"/>
<connect gate="G$1" pin="P14" pad="P14"/>
<connect gate="G$1" pin="P15" pad="P15"/>
<connect gate="G$1" pin="P16" pad="P16"/>
<connect gate="G$1" pin="P17" pad="P17"/>
<connect gate="G$1" pin="P18" pad="P18"/>
<connect gate="G$1" pin="P19" pad="P19"/>
<connect gate="G$1" pin="P2" pad="P2"/>
<connect gate="G$1" pin="P20" pad="P20"/>
<connect gate="G$1" pin="P21" pad="P21"/>
<connect gate="G$1" pin="P22" pad="P22"/>
<connect gate="G$1" pin="P23" pad="P23"/>
<connect gate="G$1" pin="P24" pad="P24"/>
<connect gate="G$1" pin="P25" pad="P25"/>
<connect gate="G$1" pin="P26" pad="P26"/>
<connect gate="G$1" pin="P27" pad="P27"/>
<connect gate="G$1" pin="P28" pad="P28"/>
<connect gate="G$1" pin="P29" pad="P29"/>
<connect gate="G$1" pin="P3" pad="P3"/>
<connect gate="G$1" pin="P30" pad="P30"/>
<connect gate="G$1" pin="P4" pad="P4"/>
<connect gate="G$1" pin="P5" pad="P5"/>
<connect gate="G$1" pin="P6" pad="P6"/>
<connect gate="G$1" pin="P7" pad="P7"/>
<connect gate="G$1" pin="P8" pad="P8"/>
<connect gate="G$1" pin="P9" pad="P9"/>
</connects>
<technologies>
<technology name=""/>
</technologies>
</device>
</devices>
</deviceset>
</devicesets>
</library>
<library name="jst-ph">
<description>&lt;b&gt;JST Connectors PH Series&lt;/b&gt;
&lt;p&gt;
&lt;author&gt;Created by yuhki50@gmail.com&lt;/author&gt;
&lt;/p&gt;</description>
<packages>
<package name="B4B-PH-K-S">
<wire x1="-4.95" y1="1.7" x2="-4.95" y2="1.175" width="0.1524" layer="21"/>
<wire x1="-4.95" y1="1.175" x2="-4.95" y2="0.25" width="0.1524" layer="21"/>
<wire x1="-4.95" y1="0.25" x2="-4.95" y2="-2.8" width="0.1524" layer="21"/>
<wire x1="-4.95" y1="1.7" x2="-2.5" y2="1.7" width="0.1524" layer="21"/>
<wire x1="-2.5" y1="1.7" x2="2.5" y2="1.7" width="0.1524" layer="21"/>
<wire x1="2.5" y1="1.7" x2="4.95" y2="1.7" width="0.1524" layer="21"/>
<wire x1="4.95" y1="-2.8" x2="-4.95" y2="-2.8" width="0.1524" layer="21"/>
<pad name="1" x="-3" y="0" drill="0.8" shape="square" rot="R90"/>
<pad name="2" x="-1" y="0" drill="0.8" rot="R90"/>
<text x="-5" y="2.5" size="1.27" layer="25" ratio="10">&gt;NAME</text>
<text x="-5" y="-4.5" size="1.27" layer="27">&gt;VALUE</text>
<wire x1="4.95" y1="1.7" x2="4.95" y2="1.175" width="0.1524" layer="21"/>
<wire x1="4.95" y1="1.175" x2="4.95" y2="0.25" width="0.1524" layer="21"/>
<wire x1="4.95" y1="0.25" x2="4.95" y2="-2.8" width="0.1524" layer="21"/>
<wire x1="-4.95" y1="0.25" x2="-4.425" y2="0.25" width="0.1524" layer="21"/>
<wire x1="-4.425" y1="0.25" x2="-4.425" y2="-2.275" width="0.1524" layer="21"/>
<wire x1="-4.425" y1="-2.275" x2="4.425" y2="-2.275" width="0.1524" layer="21"/>
<wire x1="4.425" y1="-2.275" x2="4.425" y2="0.25" width="0.1524" layer="21"/>
<wire x1="4.425" y1="0.25" x2="4.95" y2="0.25" width="0.1524" layer="21"/>
<wire x1="-4.95" y1="1.175" x2="-2.5" y2="1.175" width="0.1524" layer="21"/>
<wire x1="-2.5" y1="1.175" x2="-2.5" y2="1.7" width="0.1524" layer="21"/>
<wire x1="2.5" y1="1.7" x2="2.5" y2="1.175" width="0.1524" layer="21"/>
<wire x1="2.5" y1="1.175" x2="4.95" y2="1.175" width="0.1524" layer="21"/>
<pad name="3" x="1" y="0" drill="0.8" rot="R90"/>
<pad name="4" x="3" y="0" drill="0.8" rot="R90"/>
</package>
<package name="B4B-PH-SM4-TB">
<wire x1="-5.95" y1="1.7" x2="-5.95" y2="1.175" width="0.1524" layer="51"/>
<wire x1="-5.95" y1="1.175" x2="-5.95" y2="0.25" width="0.1524" layer="51"/>
<wire x1="-5.95" y1="0.25" x2="-5.95" y2="-2.8" width="0.1524" layer="51"/>
<wire x1="-5.95" y1="1.7" x2="-2.5" y2="1.7" width="0.1524" layer="51"/>
<wire x1="-2.5" y1="1.7" x2="2.5" y2="1.7" width="0.1524" layer="51"/>
<wire x1="2.5" y1="1.7" x2="5.95" y2="1.7" width="0.1524" layer="51"/>
<wire x1="5.95" y1="-2.8" x2="-5.95" y2="-2.8" width="0.1524" layer="51"/>
<text x="-6" y="2.5" size="1.27" layer="25" ratio="10">&gt;NAME</text>
<text x="-6" y="-7.5" size="1.27" layer="27">&gt;VALUE</text>
<wire x1="5.95" y1="1.7" x2="5.95" y2="1.175" width="0.1524" layer="51"/>
<wire x1="5.95" y1="1.175" x2="5.95" y2="0.25" width="0.1524" layer="51"/>
<wire x1="5.95" y1="0.25" x2="5.95" y2="-2.8" width="0.1524" layer="51"/>
<wire x1="-5.95" y1="0.25" x2="-4.425" y2="0.25" width="0.1524" layer="51"/>
<wire x1="-4.425" y1="0.25" x2="-4.425" y2="-2.275" width="0.1524" layer="51"/>
<wire x1="-4.425" y1="-2.275" x2="4.425" y2="-2.275" width="0.1524" layer="51"/>
<wire x1="4.425" y1="-2.275" x2="4.425" y2="0.25" width="0.1524" layer="51"/>
<wire x1="4.425" y1="0.25" x2="5.95" y2="0.25" width="0.1524" layer="51"/>
<wire x1="-5.95" y1="1.175" x2="-2.5" y2="1.175" width="0.1524" layer="51"/>
<wire x1="-2.5" y1="1.175" x2="-2.5" y2="1.7" width="0.1524" layer="51"/>
<wire x1="2.5" y1="1.7" x2="2.5" y2="1.175" width="0.1524" layer="51"/>
<wire x1="2.5" y1="1.175" x2="5.95" y2="1.175" width="0.1524" layer="51"/>
<smd name="S1" x="-5" y="-0.8" dx="3" dy="1.6" layer="1" rot="R90"/>
<smd name="S2" x="5" y="-0.8" dx="3" dy="1.6" layer="1" rot="R90"/>
<smd name="1" x="-3" y="-3.05" dx="5.5" dy="1" layer="1" rot="R90"/>
<smd name="2" x="-1" y="-3.05" dx="5.5" dy="1" layer="1" rot="R90"/>
<wire x1="-5.95" y1="1.7" x2="-5.95" y2="1.175" width="0.1524" layer="21"/>
<wire x1="-5.95" y1="1.7" x2="-2.5" y2="1.7" width="0.1524" layer="21"/>
<wire x1="-2.5" y1="1.7" x2="2.5" y2="1.7" width="0.1524" layer="21"/>
<wire x1="2.5" y1="1.7" x2="5.95" y2="1.7" width="0.1524" layer="21"/>
<wire x1="5.95" y1="1.7" x2="5.95" y2="1.175" width="0.1524" layer="21"/>
<wire x1="-5.95" y1="1.175" x2="-2.5" y2="1.175" width="0.1524" layer="21"/>
<wire x1="-2.5" y1="1.175" x2="-2.5" y2="1.7" width="0.1524" layer="21"/>
<wire x1="2.5" y1="1.7" x2="2.5" y2="1.175" width="0.1524" layer="21"/>
<wire x1="2.5" y1="1.175" x2="5.95" y2="1.175" width="0.1524" layer="21"/>
<wire x1="5.95" y1="-2.8" x2="3.8" y2="-2.8" width="0.1524" layer="21"/>
<wire x1="-3.8" y1="-2.8" x2="-5.95" y2="-2.8" width="0.1524" layer="21"/>
<wire x1="-5.95" y1="1.175" x2="-5.95" y2="-2.8" width="0.1524" layer="21"/>
<wire x1="5.95" y1="1.175" x2="5.95" y2="-2.8" width="0.1524" layer="21"/>
<smd name="3" x="1" y="-3.05" dx="5.5" dy="1" layer="1" rot="R90"/>
<smd name="4" x="3" y="-3.05" dx="5.5" dy="1" layer="1" rot="R90"/>
</package>
</packages>
<symbols>
<symbol name="CON-1X4">
<wire x1="-3.81" y1="-7.62" x2="3.81" y2="-7.62" width="0.4064" layer="94"/>
<wire x1="3.81" y1="-7.62" x2="3.81" y2="5.08" width="0.4064" layer="94"/>
<wire x1="3.81" y1="5.08" x2="-3.81" y2="5.08" width="0.4064" layer="94"/>
<wire x1="-3.81" y1="5.08" x2="-3.81" y2="-7.62" width="0.4064" layer="94"/>
<text x="-3.81" y="6.35" size="1.778" layer="95">&gt;NAME</text>
<text x="-3.81" y="-10.16" size="1.778" layer="96">&gt;VALUE</text>
<pin name="1" x="0" y="2.54" visible="pad" length="short" direction="pas" function="dot"/>
<pin name="2" x="0" y="0" visible="pad" length="short" direction="pas" function="dot"/>
<pin name="3" x="0" y="-2.54" visible="pad" length="short" direction="pas" function="dot"/>
<pin name="4" x="0" y="-5.08" visible="pad" length="short" direction="pas" function="dot"/>
</symbol>
</symbols>
<devicesets>
<deviceset name="B4B-PH-*" prefix="CN" uservalue="yes">
<description>&lt;b&gt;Wire-to-Board 2.0mm pitch top mount connector&lt;/b&gt;
&lt;p&gt;
Source:
&lt;ul&gt;
&lt;li&gt;http://www.jst-mfg.com/product/pdf/jpn/PH.pdf&lt;/li&gt;
&lt;li&gt;http://www.jst-mfg.com/product/detail.php?series=199&lt;/li&gt;
&lt;ul&gt;
&lt;/p&gt;</description>
<gates>
<gate name="G$1" symbol="CON-1X4" x="0" y="0"/>
</gates>
<devices>
<device name="K-S" package="B4B-PH-K-S">
<connects>
<connect gate="G$1" pin="1" pad="1"/>
<connect gate="G$1" pin="2" pad="2"/>
<connect gate="G$1" pin="3" pad="3"/>
<connect gate="G$1" pin="4" pad="4"/>
</connects>
<technologies>
<technology name=""/>
</technologies>
</device>
<device name="SM4-TB" package="B4B-PH-SM4-TB">
<connects>
<connect gate="G$1" pin="1" pad="1"/>
<connect gate="G$1" pin="2" pad="2"/>
<connect gate="G$1" pin="3" pad="3"/>
<connect gate="G$1" pin="4" pad="4"/>
</connects>
<technologies>
<technology name=""/>
</technologies>
</device>
</devices>
</deviceset>
</devicesets>
</library>
<library name="pins">
<packages>
<package name="P2_7_1.27">
<pad name="P1" x="0" y="3.81" drill="0.65" diameter="1.016"/>
<pad name="P2" x="1.27" y="3.81" drill="0.65" diameter="1.016"/>
<pad name="P3" x="0" y="2.54" drill="0.65" diameter="1.016"/>
<pad name="P4" x="1.27" y="2.54" drill="0.65" diameter="1.016"/>
<pad name="P5" x="0" y="1.27" drill="0.65" diameter="1.016"/>
<pad name="P6" x="1.27" y="1.27" drill="0.65" diameter="1.016"/>
<pad name="P7" x="0" y="0" drill="0.65" diameter="1.016"/>
<pad name="P8" x="1.27" y="0" drill="0.65" diameter="1.016"/>
<pad name="P9" x="0" y="-1.27" drill="0.65" diameter="1.016"/>
<pad name="P10" x="1.27" y="-1.27" drill="0.65" diameter="1.016"/>
<pad name="P11" x="0" y="-2.54" drill="0.65" diameter="1.016"/>
<pad name="P12" x="1.27" y="-2.54" drill="0.65" diameter="1.016"/>
<pad name="P13" x="0" y="-3.81" drill="0.65" diameter="1.016"/>
<pad name="P14" x="1.27" y="-3.81" drill="0.65" diameter="1.016"/>
</package>
</packages>
<symbols>
<symbol name="P14">
<pin name="P1" x="5.08" y="15.24" length="short" rot="R180"/>
<pin name="P2" x="5.08" y="12.7" length="short" rot="R180"/>
<pin name="P3" x="5.08" y="10.16" length="short" rot="R180"/>
<pin name="P4" x="5.08" y="7.62" length="short" rot="R180"/>
<pin name="P5" x="5.08" y="5.08" length="short" rot="R180"/>
<pin name="P6" x="5.08" y="2.54" length="short" rot="R180"/>
<pin name="P7" x="5.08" y="0" length="short" rot="R180"/>
<pin name="P8" x="5.08" y="-2.54" length="short" rot="R180"/>
<pin name="P9" x="5.08" y="-5.08" length="short" rot="R180"/>
<pin name="P10" x="5.08" y="-7.62" length="short" rot="R180"/>
<pin name="P11" x="5.08" y="-10.16" length="short" rot="R180"/>
<pin name="P12" x="5.08" y="-12.7" length="short" rot="R180"/>
<pin name="P13" x="5.08" y="-15.24" length="short" rot="R180"/>
<pin name="P14" x="5.08" y="-17.78" length="short" rot="R180"/>
<wire x1="-7.62" y1="17.78" x2="2.54" y2="17.78" width="0.254" layer="94"/>
<wire x1="2.54" y1="17.78" x2="2.54" y2="-20.32" width="0.254" layer="94"/>
<wire x1="2.54" y1="-20.32" x2="-7.62" y2="-20.32" width="0.254" layer="94"/>
<wire x1="-7.62" y1="-20.32" x2="-7.62" y2="17.78" width="0.254" layer="94"/>
<text x="-7.62" y="18.034" size="1.27" layer="95">&gt;NAME</text>
<text x="-7.62" y="-22.86" size="1.27" layer="96">&gt;VALUE</text>
</symbol>
</symbols>
<devicesets>
<deviceset name="P2_7_1.27">
<gates>
<gate name="G$1" symbol="P14" x="0" y="0"/>
</gates>
<devices>
<device name="" package="P2_7_1.27">
<connects>
<connect gate="G$1" pin="P1" pad="P1"/>
<connect gate="G$1" pin="P10" pad="P10"/>
<connect gate="G$1" pin="P11" pad="P11"/>
<connect gate="G$1" pin="P12" pad="P12"/>
<connect gate="G$1" pin="P13" pad="P13"/>
<connect gate="G$1" pin="P14" pad="P14"/>
<connect gate="G$1" pin="P2" pad="P2"/>
<connect gate="G$1" pin="P3" pad="P3"/>
<connect gate="G$1" pin="P4" pad="P4"/>
<connect gate="G$1" pin="P5" pad="P5"/>
<connect gate="G$1" pin="P6" pad="P6"/>
<connect gate="G$1" pin="P7" pad="P7"/>
<connect gate="G$1" pin="P8" pad="P8"/>
<connect gate="G$1" pin="P9" pad="P9"/>
</connects>
<technologies>
<technology name=""/>
</technologies>
</device>
</devices>
</deviceset>
</devicesets>
</library>
<library name="supply1" urn="urn:adsk.eagle:library:371">
<description>&lt;b&gt;Supply Symbols&lt;/b&gt;&lt;p&gt;
 GND, VCC, 0V, +5V, -5V, etc.&lt;p&gt;
 Please keep in mind, that these devices are necessary for the
 automatic wiring of the supply signals.&lt;p&gt;
 The pin name defined in the symbol is identical to the net which is to be wired automatically.&lt;p&gt;
 In this library the device names are the same as the pin names of the symbols, therefore the correct signal names appear next to the supply symbols in the schematic.&lt;p&gt;
 &lt;author&gt;Created by librarian@cadsoft.de&lt;/author&gt;</description>
<packages>
</packages>
<symbols>
<symbol name="GND" urn="urn:adsk.eagle:symbol:26925/1" library_version="1">
<wire x1="-1.905" y1="0" x2="1.905" y2="0" width="0.254" layer="94"/>
<text x="-2.54" y="-2.54" size="1.778" layer="96">&gt;VALUE</text>
<pin name="GND" x="0" y="2.54" visible="off" length="short" direction="sup" rot="R270"/>
</symbol>
</symbols>
<devicesets>
<deviceset name="GND" urn="urn:adsk.eagle:component:26954/1" prefix="GND" library_version="1">
<description>&lt;b&gt;SUPPLY SYMBOL&lt;/b&gt;</description>
<gates>
<gate name="1" symbol="GND" x="0" y="0"/>
</gates>
<devices>
<device name="">
<technologies>
<technology name=""/>
</technologies>
</device>
</devices>
</deviceset>
</devicesets>
</library>
</libraries>
<attributes>
</attributes>
<variantdefs>
</variantdefs>
<classes>
<class number="0" name="default" width="0" drill="0">
</class>
</classes>
<parts>
<part name="U$1" library="card_edge" deviceset="CR22A-30D-2.54DS" device=""/>
<part name="U$2" library="card_edge" deviceset="CR22A-30D-2.54DS" device=""/>
<part name="U$3" library="card_edge" deviceset="CR22A-30D-2.54DS" device=""/>
<part name="U$4" library="card_edge" deviceset="CR22A-30D-2.54DS" device=""/>
<part name="U$5" library="card_edge" deviceset="CR22A-30D-2.54DS" device=""/>
<part name="U$6" library="card_edge" deviceset="CR22A-30D-2.54DS" device=""/>
<part name="CN1" library="jst-ph" deviceset="B4B-PH-*" device="K-S"/>
<part name="CN2" library="jst-ph" deviceset="B4B-PH-*" device="K-S"/>
<part name="U$8" library="con-pci_express(pci-e)" deviceset="PCI-E16X_DATA_EDGE" device=""/>
<part name="U$7" library="pins" deviceset="P2_7_1.27" device=""/>
<part name="GND1" library="supply1" library_urn="urn:adsk.eagle:library:371" deviceset="GND" device=""/>
<part name="GND2" library="supply1" library_urn="urn:adsk.eagle:library:371" deviceset="GND" device=""/>
<part name="GND3" library="supply1" library_urn="urn:adsk.eagle:library:371" deviceset="GND" device=""/>
<part name="GND4" library="supply1" library_urn="urn:adsk.eagle:library:371" deviceset="GND" device=""/>
<part name="GND5" library="supply1" library_urn="urn:adsk.eagle:library:371" deviceset="GND" device=""/>
<part name="GND6" library="supply1" library_urn="urn:adsk.eagle:library:371" deviceset="GND" device=""/>
<part name="GND7" library="supply1" library_urn="urn:adsk.eagle:library:371" deviceset="GND" device=""/>
<part name="GND8" library="supply1" library_urn="urn:adsk.eagle:library:371" deviceset="GND" device=""/>
<part name="GND9" library="supply1" library_urn="urn:adsk.eagle:library:371" deviceset="GND" device=""/>
<part name="GND10" library="supply1" library_urn="urn:adsk.eagle:library:371" deviceset="GND" device=""/>
<part name="GND11" library="supply1" library_urn="urn:adsk.eagle:library:371" deviceset="GND" device=""/>
<part name="GND12" library="supply1" library_urn="urn:adsk.eagle:library:371" deviceset="GND" device=""/>
</parts>
<sheets>
<sheet>
<plain>
</plain>
<instances>
<instance part="U$1" gate="G$1" x="5.08" y="101.6" smashed="yes">
<attribute name="NAME" x="-2.54" y="142.494" size="1.27" layer="95"/>
<attribute name="VALUE" x="-2.54" y="60.96" size="1.27" layer="96"/>
</instance>
<instance part="U$2" gate="G$1" x="33.02" y="101.6" smashed="yes">
<attribute name="NAME" x="25.4" y="142.494" size="1.27" layer="95"/>
<attribute name="VALUE" x="25.4" y="60.96" size="1.27" layer="96"/>
</instance>
<instance part="U$3" gate="G$1" x="60.96" y="101.6" smashed="yes">
<attribute name="NAME" x="53.34" y="142.494" size="1.27" layer="95"/>
<attribute name="VALUE" x="53.34" y="60.96" size="1.27" layer="96"/>
</instance>
<instance part="U$4" gate="G$1" x="88.9" y="101.6" smashed="yes">
<attribute name="NAME" x="81.28" y="142.494" size="1.27" layer="95"/>
<attribute name="VALUE" x="81.28" y="60.96" size="1.27" layer="96"/>
</instance>
<instance part="U$5" gate="G$1" x="116.84" y="101.6" smashed="yes">
<attribute name="NAME" x="109.22" y="142.494" size="1.27" layer="95"/>
<attribute name="VALUE" x="109.22" y="60.96" size="1.27" layer="96"/>
</instance>
<instance part="U$6" gate="G$1" x="144.78" y="101.6" smashed="yes">
<attribute name="NAME" x="137.16" y="142.494" size="1.27" layer="95"/>
<attribute name="VALUE" x="137.16" y="60.96" size="1.27" layer="96"/>
</instance>
<instance part="CN1" gate="G$1" x="200.66" y="137.16" smashed="yes">
<attribute name="NAME" x="196.85" y="143.51" size="1.778" layer="95"/>
<attribute name="VALUE" x="196.85" y="127" size="1.778" layer="96"/>
</instance>
<instance part="CN2" gate="G$1" x="200.66" y="116.84" smashed="yes">
<attribute name="NAME" x="196.85" y="123.19" size="1.778" layer="95"/>
<attribute name="VALUE" x="196.85" y="106.68" size="1.778" layer="96"/>
</instance>
<instance part="U$8" gate="G$1" x="81.28" y="17.78" smashed="yes" rot="R90">
<attribute name="NAME" x="88.9" y="114.3" size="1.27" layer="95" rot="R180"/>
<attribute name="VALUE" x="50.8" y="20.32" size="1.27" layer="96" rot="R180"/>
</instance>
<instance part="U$7" gate="G$1" x="193.04" y="83.82" smashed="yes" rot="MR0">
<attribute name="NAME" x="200.66" y="101.854" size="1.27" layer="95" rot="MR0"/>
<attribute name="VALUE" x="200.66" y="60.96" size="1.27" layer="96" rot="MR0"/>
</instance>
<instance part="GND1" gate="1" x="0" y="0" smashed="yes">
<attribute name="VALUE" x="-2.54" y="-2.54" size="1.778" layer="96"/>
</instance>
<instance part="GND2" gate="1" x="0" y="38.1" smashed="yes" rot="R180">
<attribute name="VALUE" x="2.54" y="40.64" size="1.778" layer="96" rot="R180"/>
</instance>
<instance part="GND3" gate="1" x="27.94" y="38.1" smashed="yes" rot="R180">
<attribute name="VALUE" x="30.48" y="40.64" size="1.778" layer="96" rot="R180"/>
</instance>
<instance part="GND4" gate="1" x="27.94" y="0" smashed="yes">
<attribute name="VALUE" x="25.4" y="-2.54" size="1.778" layer="96"/>
</instance>
<instance part="GND5" gate="1" x="53.34" y="0" smashed="yes">
<attribute name="VALUE" x="50.8" y="-2.54" size="1.778" layer="96"/>
</instance>
<instance part="GND6" gate="1" x="78.74" y="0" smashed="yes">
<attribute name="VALUE" x="76.2" y="-2.54" size="1.778" layer="96"/>
</instance>
<instance part="GND7" gate="1" x="104.14" y="0" smashed="yes">
<attribute name="VALUE" x="101.6" y="-2.54" size="1.778" layer="96"/>
</instance>
<instance part="GND8" gate="1" x="129.54" y="0" smashed="yes">
<attribute name="VALUE" x="127" y="-2.54" size="1.778" layer="96"/>
</instance>
<instance part="GND9" gate="1" x="129.54" y="38.1" smashed="yes" rot="R180">
<attribute name="VALUE" x="132.08" y="40.64" size="1.778" layer="96" rot="R180"/>
</instance>
<instance part="GND10" gate="1" x="104.14" y="38.1" smashed="yes" rot="R180">
<attribute name="VALUE" x="106.68" y="40.64" size="1.778" layer="96" rot="R180"/>
</instance>
<instance part="GND11" gate="1" x="78.74" y="38.1" smashed="yes" rot="R180">
<attribute name="VALUE" x="81.28" y="40.64" size="1.778" layer="96" rot="R180"/>
</instance>
<instance part="GND12" gate="1" x="53.34" y="38.1" smashed="yes" rot="R180">
<attribute name="VALUE" x="55.88" y="40.64" size="1.778" layer="96" rot="R180"/>
</instance>
</instances>
<busses>
</busses>
<nets>
<net name="VCC" class="0">
<segment>
<pinref part="U$1" gate="G$1" pin="P2"/>
<wire x1="10.16" y1="137.16" x2="12.7" y2="137.16" width="0.1524" layer="91"/>
<label x="12.7" y="137.16" size="1.778" layer="95" xref="yes"/>
</segment>
<segment>
<wire x1="38.1" y1="137.16" x2="40.64" y2="137.16" width="0.1524" layer="91"/>
<label x="40.64" y="137.16" size="1.778" layer="95" xref="yes"/>
<pinref part="U$2" gate="G$1" pin="P2"/>
</segment>
<segment>
<wire x1="66.04" y1="137.16" x2="68.58" y2="137.16" width="0.1524" layer="91"/>
<label x="68.58" y="137.16" size="1.778" layer="95" xref="yes"/>
<pinref part="U$3" gate="G$1" pin="P2"/>
</segment>
<segment>
<wire x1="93.98" y1="137.16" x2="96.52" y2="137.16" width="0.1524" layer="91"/>
<label x="96.52" y="137.16" size="1.778" layer="95" xref="yes"/>
<pinref part="U$4" gate="G$1" pin="P2"/>
</segment>
<segment>
<wire x1="121.92" y1="137.16" x2="124.46" y2="137.16" width="0.1524" layer="91"/>
<label x="124.46" y="137.16" size="1.778" layer="95" xref="yes"/>
<pinref part="U$5" gate="G$1" pin="P2"/>
</segment>
<segment>
<wire x1="149.86" y1="137.16" x2="152.4" y2="137.16" width="0.1524" layer="91"/>
<label x="152.4" y="137.16" size="1.778" layer="95" xref="yes"/>
<pinref part="U$6" gate="G$1" pin="P2"/>
</segment>
</net>
<net name="VDD" class="0">
<segment>
<pinref part="U$1" gate="G$1" pin="P3"/>
<wire x1="10.16" y1="134.62" x2="12.7" y2="134.62" width="0.1524" layer="91"/>
<label x="12.7" y="134.62" size="1.778" layer="95" xref="yes"/>
</segment>
<segment>
<wire x1="38.1" y1="134.62" x2="40.64" y2="134.62" width="0.1524" layer="91"/>
<label x="40.64" y="134.62" size="1.778" layer="95" xref="yes"/>
<pinref part="U$2" gate="G$1" pin="P3"/>
</segment>
<segment>
<wire x1="66.04" y1="134.62" x2="68.58" y2="134.62" width="0.1524" layer="91"/>
<label x="68.58" y="134.62" size="1.778" layer="95" xref="yes"/>
<pinref part="U$3" gate="G$1" pin="P3"/>
</segment>
<segment>
<wire x1="93.98" y1="134.62" x2="96.52" y2="134.62" width="0.1524" layer="91"/>
<label x="96.52" y="134.62" size="1.778" layer="95" xref="yes"/>
<pinref part="U$4" gate="G$1" pin="P3"/>
</segment>
<segment>
<wire x1="121.92" y1="134.62" x2="124.46" y2="134.62" width="0.1524" layer="91"/>
<label x="124.46" y="134.62" size="1.778" layer="95" xref="yes"/>
<pinref part="U$5" gate="G$1" pin="P3"/>
</segment>
<segment>
<wire x1="149.86" y1="134.62" x2="152.4" y2="134.62" width="0.1524" layer="91"/>
<label x="152.4" y="134.62" size="1.778" layer="95" xref="yes"/>
<pinref part="U$6" gate="G$1" pin="P3"/>
</segment>
</net>
<net name="VBU" class="0">
<segment>
<pinref part="U$1" gate="G$1" pin="P4"/>
<wire x1="10.16" y1="132.08" x2="12.7" y2="132.08" width="0.1524" layer="91"/>
<label x="12.7" y="132.08" size="1.778" layer="95" xref="yes"/>
</segment>
<segment>
<wire x1="38.1" y1="132.08" x2="40.64" y2="132.08" width="0.1524" layer="91"/>
<label x="40.64" y="132.08" size="1.778" layer="95" xref="yes"/>
<pinref part="U$2" gate="G$1" pin="P4"/>
</segment>
<segment>
<wire x1="66.04" y1="132.08" x2="68.58" y2="132.08" width="0.1524" layer="91"/>
<label x="68.58" y="132.08" size="1.778" layer="95" xref="yes"/>
<pinref part="U$3" gate="G$1" pin="P4"/>
</segment>
<segment>
<wire x1="93.98" y1="132.08" x2="96.52" y2="132.08" width="0.1524" layer="91"/>
<label x="96.52" y="132.08" size="1.778" layer="95" xref="yes"/>
<pinref part="U$4" gate="G$1" pin="P4"/>
</segment>
<segment>
<wire x1="121.92" y1="132.08" x2="124.46" y2="132.08" width="0.1524" layer="91"/>
<label x="124.46" y="132.08" size="1.778" layer="95" xref="yes"/>
<pinref part="U$5" gate="G$1" pin="P4"/>
</segment>
<segment>
<wire x1="149.86" y1="132.08" x2="152.4" y2="132.08" width="0.1524" layer="91"/>
<label x="152.4" y="132.08" size="1.778" layer="95" xref="yes"/>
<pinref part="U$6" gate="G$1" pin="P4"/>
</segment>
</net>
<net name="GND" class="0">
<segment>
<pinref part="U$1" gate="G$1" pin="P5"/>
<wire x1="10.16" y1="129.54" x2="12.7" y2="129.54" width="0.1524" layer="91"/>
<label x="12.7" y="129.54" size="1.778" layer="95" xref="yes"/>
</segment>
<segment>
<pinref part="U$1" gate="G$1" pin="P8"/>
<wire x1="10.16" y1="121.92" x2="12.7" y2="121.92" width="0.1524" layer="91"/>
<label x="12.7" y="121.92" size="1.778" layer="95" xref="yes"/>
</segment>
<segment>
<wire x1="38.1" y1="129.54" x2="40.64" y2="129.54" width="0.1524" layer="91"/>
<label x="40.64" y="129.54" size="1.778" layer="95" xref="yes"/>
<pinref part="U$2" gate="G$1" pin="P5"/>
</segment>
<segment>
<wire x1="66.04" y1="129.54" x2="68.58" y2="129.54" width="0.1524" layer="91"/>
<label x="68.58" y="129.54" size="1.778" layer="95" xref="yes"/>
<pinref part="U$3" gate="G$1" pin="P5"/>
</segment>
<segment>
<wire x1="93.98" y1="129.54" x2="96.52" y2="129.54" width="0.1524" layer="91"/>
<label x="96.52" y="129.54" size="1.778" layer="95" xref="yes"/>
<pinref part="U$4" gate="G$1" pin="P5"/>
</segment>
<segment>
<wire x1="121.92" y1="129.54" x2="124.46" y2="129.54" width="0.1524" layer="91"/>
<label x="124.46" y="129.54" size="1.778" layer="95" xref="yes"/>
<pinref part="U$5" gate="G$1" pin="P5"/>
</segment>
<segment>
<wire x1="149.86" y1="129.54" x2="152.4" y2="129.54" width="0.1524" layer="91"/>
<label x="152.4" y="129.54" size="1.778" layer="95" xref="yes"/>
<pinref part="U$6" gate="G$1" pin="P5"/>
</segment>
<segment>
<wire x1="38.1" y1="121.92" x2="40.64" y2="121.92" width="0.1524" layer="91"/>
<label x="40.64" y="121.92" size="1.778" layer="95" xref="yes"/>
<pinref part="U$2" gate="G$1" pin="P8"/>
</segment>
<segment>
<wire x1="66.04" y1="121.92" x2="68.58" y2="121.92" width="0.1524" layer="91"/>
<label x="68.58" y="121.92" size="1.778" layer="95" xref="yes"/>
<pinref part="U$3" gate="G$1" pin="P8"/>
</segment>
<segment>
<wire x1="93.98" y1="121.92" x2="96.52" y2="121.92" width="0.1524" layer="91"/>
<label x="96.52" y="121.92" size="1.778" layer="95" xref="yes"/>
<pinref part="U$4" gate="G$1" pin="P8"/>
</segment>
<segment>
<wire x1="121.92" y1="121.92" x2="124.46" y2="121.92" width="0.1524" layer="91"/>
<label x="124.46" y="121.92" size="1.778" layer="95" xref="yes"/>
<pinref part="U$5" gate="G$1" pin="P8"/>
</segment>
<segment>
<wire x1="149.86" y1="121.92" x2="152.4" y2="121.92" width="0.1524" layer="91"/>
<label x="152.4" y="121.92" size="1.778" layer="95" xref="yes"/>
<pinref part="U$6" gate="G$1" pin="P8"/>
<label x="152.4" y="121.92" size="1.778" layer="95" xref="yes"/>
</segment>
<segment>
<pinref part="CN1" gate="G$1" pin="4"/>
<wire x1="200.66" y1="132.08" x2="193.04" y2="132.08" width="0.1524" layer="91"/>
<label x="193.04" y="132.08" size="1.778" layer="95" rot="MR0" xref="yes"/>
</segment>
<segment>
<wire x1="200.66" y1="111.76" x2="193.04" y2="111.76" width="0.1524" layer="91"/>
<label x="193.04" y="111.76" size="1.778" layer="95" rot="MR0" xref="yes"/>
<pinref part="CN2" gate="G$1" pin="4"/>
</segment>
<segment>
<wire x1="187.96" y1="88.9" x2="185.42" y2="88.9" width="0.1524" layer="91"/>
<label x="185.42" y="88.9" size="1.778" layer="95" rot="MR0" xref="yes"/>
<pinref part="U$7" gate="G$1" pin="P5"/>
</segment>
<segment>
<wire x1="185.42" y1="83.82" x2="187.96" y2="83.82" width="0.1524" layer="91"/>
<label x="185.42" y="83.82" size="1.778" layer="95" rot="MR0" xref="yes"/>
<pinref part="U$7" gate="G$1" pin="P7"/>
</segment>
<segment>
<wire x1="187.96" y1="73.66" x2="185.42" y2="73.66" width="0.1524" layer="91"/>
<label x="185.42" y="73.66" size="1.778" layer="95" rot="MR0" xref="yes"/>
<pinref part="U$7" gate="G$1" pin="P11"/>
</segment>
<segment>
<pinref part="U$8" gate="G$1" pin="A15"/>
<wire x1="5.08" y1="5.08" x2="5.08" y2="2.54" width="0.1524" layer="91"/>
<wire x1="5.08" y1="2.54" x2="2.54" y2="2.54" width="0.1524" layer="91"/>
<pinref part="U$8" gate="G$1" pin="A12"/>
<wire x1="2.54" y1="2.54" x2="0" y2="2.54" width="0.1524" layer="91"/>
<wire x1="0" y1="2.54" x2="-2.54" y2="2.54" width="0.1524" layer="91"/>
<wire x1="-2.54" y1="2.54" x2="-2.54" y2="5.08" width="0.1524" layer="91"/>
<pinref part="U$8" gate="G$1" pin="A13"/>
<wire x1="0" y1="5.08" x2="0" y2="2.54" width="0.1524" layer="91"/>
<junction x="0" y="2.54"/>
<pinref part="U$8" gate="G$1" pin="A14"/>
<wire x1="2.54" y1="5.08" x2="2.54" y2="2.54" width="0.1524" layer="91"/>
<junction x="2.54" y="2.54"/>
<pinref part="GND1" gate="1" pin="GND"/>
</segment>
<segment>
<pinref part="U$8" gate="G$1" pin="B15"/>
<wire x1="5.08" y1="33.02" x2="5.08" y2="35.56" width="0.1524" layer="91"/>
<wire x1="5.08" y1="35.56" x2="2.54" y2="35.56" width="0.1524" layer="91"/>
<pinref part="U$8" gate="G$1" pin="B12"/>
<wire x1="2.54" y1="35.56" x2="0" y2="35.56" width="0.1524" layer="91"/>
<wire x1="0" y1="35.56" x2="-2.54" y2="35.56" width="0.1524" layer="91"/>
<wire x1="-2.54" y1="35.56" x2="-2.54" y2="33.02" width="0.1524" layer="91"/>
<pinref part="U$8" gate="G$1" pin="B13"/>
<wire x1="0" y1="33.02" x2="0" y2="35.56" width="0.1524" layer="91"/>
<junction x="0" y="35.56"/>
<pinref part="U$8" gate="G$1" pin="B14"/>
<wire x1="2.54" y1="35.56" x2="2.54" y2="33.02" width="0.1524" layer="91"/>
<junction x="2.54" y="35.56"/>
<pinref part="GND2" gate="1" pin="GND"/>
</segment>
<segment>
<wire x1="27.94" y1="33.02" x2="27.94" y2="35.56" width="0.1524" layer="91"/>
<pinref part="U$8" gate="G$1" pin="B24"/>
<wire x1="30.48" y1="33.02" x2="30.48" y2="35.56" width="0.1524" layer="91"/>
<pinref part="U$8" gate="G$1" pin="B25"/>
<wire x1="27.94" y1="35.56" x2="30.48" y2="35.56" width="0.1524" layer="91"/>
<pinref part="GND3" gate="1" pin="GND"/>
<junction x="27.94" y="35.56"/>
</segment>
<segment>
<wire x1="27.94" y1="5.08" x2="27.94" y2="2.54" width="0.1524" layer="91"/>
<pinref part="U$8" gate="G$1" pin="A24"/>
<pinref part="GND4" gate="1" pin="GND"/>
<wire x1="25.4" y1="5.08" x2="25.4" y2="2.54" width="0.1524" layer="91"/>
<pinref part="U$8" gate="G$1" pin="A23"/>
<wire x1="27.94" y1="2.54" x2="25.4" y2="2.54" width="0.1524" layer="91"/>
<junction x="27.94" y="2.54"/>
<pinref part="U$8" gate="G$1" pin="A25"/>
<wire x1="30.48" y1="5.08" x2="30.48" y2="2.54" width="0.1524" layer="91"/>
<wire x1="27.94" y1="2.54" x2="30.48" y2="2.54" width="0.1524" layer="91"/>
</segment>
<segment>
<wire x1="53.34" y1="5.08" x2="53.34" y2="2.54" width="0.1524" layer="91"/>
<pinref part="U$8" gate="G$1" pin="A34"/>
<pinref part="GND5" gate="1" pin="GND"/>
<wire x1="50.8" y1="5.08" x2="50.8" y2="2.54" width="0.1524" layer="91"/>
<pinref part="U$8" gate="G$1" pin="A33"/>
<wire x1="53.34" y1="2.54" x2="50.8" y2="2.54" width="0.1524" layer="91"/>
<junction x="53.34" y="2.54"/>
<wire x1="55.88" y1="5.08" x2="55.88" y2="2.54" width="0.1524" layer="91"/>
<pinref part="U$8" gate="G$1" pin="A35"/>
<wire x1="53.34" y1="2.54" x2="55.88" y2="2.54" width="0.1524" layer="91"/>
</segment>
<segment>
<wire x1="78.74" y1="5.08" x2="78.74" y2="2.54" width="0.1524" layer="91"/>
<pinref part="U$8" gate="G$1" pin="A44"/>
<pinref part="GND6" gate="1" pin="GND"/>
<wire x1="76.2" y1="5.08" x2="76.2" y2="2.54" width="0.1524" layer="91"/>
<pinref part="U$8" gate="G$1" pin="A43"/>
<wire x1="76.2" y1="2.54" x2="78.74" y2="2.54" width="0.1524" layer="91"/>
<junction x="78.74" y="2.54"/>
<wire x1="81.28" y1="5.08" x2="81.28" y2="2.54" width="0.1524" layer="91"/>
<pinref part="U$8" gate="G$1" pin="A45"/>
<wire x1="78.74" y1="2.54" x2="81.28" y2="2.54" width="0.1524" layer="91"/>
</segment>
<segment>
<wire x1="104.14" y1="5.08" x2="104.14" y2="2.54" width="0.1524" layer="91"/>
<pinref part="U$8" gate="G$1" pin="A54"/>
<pinref part="GND7" gate="1" pin="GND"/>
<wire x1="101.6" y1="5.08" x2="101.6" y2="2.54" width="0.1524" layer="91"/>
<pinref part="U$8" gate="G$1" pin="A53"/>
<wire x1="101.6" y1="2.54" x2="104.14" y2="2.54" width="0.1524" layer="91"/>
<junction x="104.14" y="2.54"/>
<wire x1="106.68" y1="5.08" x2="106.68" y2="2.54" width="0.1524" layer="91"/>
<pinref part="U$8" gate="G$1" pin="A55"/>
<wire x1="104.14" y1="2.54" x2="106.68" y2="2.54" width="0.1524" layer="91"/>
</segment>
<segment>
<wire x1="129.54" y1="5.08" x2="129.54" y2="2.54" width="0.1524" layer="91"/>
<pinref part="U$8" gate="G$1" pin="A64"/>
<pinref part="GND8" gate="1" pin="GND"/>
<wire x1="127" y1="5.08" x2="127" y2="2.54" width="0.1524" layer="91"/>
<pinref part="U$8" gate="G$1" pin="A63"/>
<wire x1="127" y1="2.54" x2="129.54" y2="2.54" width="0.1524" layer="91"/>
<junction x="129.54" y="2.54"/>
<wire x1="132.08" y1="2.54" x2="132.08" y2="5.08" width="0.1524" layer="91"/>
<pinref part="U$8" gate="G$1" pin="A65"/>
<wire x1="129.54" y1="2.54" x2="132.08" y2="2.54" width="0.1524" layer="91"/>
</segment>
<segment>
<wire x1="129.54" y1="33.02" x2="129.54" y2="35.56" width="0.1524" layer="91"/>
<pinref part="U$8" gate="G$1" pin="B64"/>
<pinref part="GND9" gate="1" pin="GND"/>
<wire x1="132.08" y1="33.02" x2="132.08" y2="35.56" width="0.1524" layer="91"/>
<pinref part="U$8" gate="G$1" pin="B65"/>
<wire x1="132.08" y1="35.56" x2="129.54" y2="35.56" width="0.1524" layer="91"/>
<junction x="129.54" y="35.56"/>
</segment>
<segment>
<wire x1="104.14" y1="33.02" x2="104.14" y2="35.56" width="0.1524" layer="91"/>
<pinref part="U$8" gate="G$1" pin="B54"/>
<pinref part="GND10" gate="1" pin="GND"/>
<wire x1="106.68" y1="33.02" x2="106.68" y2="35.56" width="0.1524" layer="91"/>
<pinref part="U$8" gate="G$1" pin="B55"/>
<wire x1="106.68" y1="35.56" x2="104.14" y2="35.56" width="0.1524" layer="91"/>
<junction x="104.14" y="35.56"/>
</segment>
<segment>
<wire x1="78.74" y1="33.02" x2="78.74" y2="35.56" width="0.1524" layer="91"/>
<pinref part="U$8" gate="G$1" pin="B44"/>
<pinref part="GND11" gate="1" pin="GND"/>
<wire x1="81.28" y1="33.02" x2="81.28" y2="35.56" width="0.1524" layer="91"/>
<pinref part="U$8" gate="G$1" pin="B45"/>
<wire x1="81.28" y1="35.56" x2="78.74" y2="35.56" width="0.1524" layer="91"/>
<junction x="78.74" y="35.56"/>
</segment>
<segment>
<wire x1="53.34" y1="33.02" x2="53.34" y2="35.56" width="0.1524" layer="91"/>
<pinref part="U$8" gate="G$1" pin="B34"/>
<pinref part="GND12" gate="1" pin="GND"/>
<wire x1="55.88" y1="33.02" x2="55.88" y2="35.56" width="0.1524" layer="91"/>
<pinref part="U$8" gate="G$1" pin="B35"/>
<wire x1="55.88" y1="35.56" x2="53.34" y2="35.56" width="0.1524" layer="91"/>
<junction x="53.34" y="35.56"/>
</segment>
</net>
<net name="CANL" class="0">
<segment>
<pinref part="U$1" gate="G$1" pin="P6"/>
<wire x1="10.16" y1="127" x2="12.7" y2="127" width="0.1524" layer="91"/>
<label x="12.7" y="127" size="1.778" layer="95" xref="yes"/>
</segment>
<segment>
<wire x1="38.1" y1="127" x2="40.64" y2="127" width="0.1524" layer="91"/>
<label x="40.64" y="127" size="1.778" layer="95" xref="yes"/>
<pinref part="U$2" gate="G$1" pin="P6"/>
</segment>
<segment>
<wire x1="66.04" y1="127" x2="68.58" y2="127" width="0.1524" layer="91"/>
<label x="68.58" y="127" size="1.778" layer="95" xref="yes"/>
<pinref part="U$3" gate="G$1" pin="P6"/>
</segment>
<segment>
<wire x1="93.98" y1="127" x2="96.52" y2="127" width="0.1524" layer="91"/>
<label x="96.52" y="127" size="1.778" layer="95" xref="yes"/>
<pinref part="U$4" gate="G$1" pin="P6"/>
</segment>
<segment>
<wire x1="121.92" y1="127" x2="124.46" y2="127" width="0.1524" layer="91"/>
<label x="124.46" y="127" size="1.778" layer="95" xref="yes"/>
<pinref part="U$5" gate="G$1" pin="P6"/>
</segment>
<segment>
<wire x1="149.86" y1="127" x2="152.4" y2="127" width="0.1524" layer="91"/>
<label x="152.4" y="127" size="1.778" layer="95" xref="yes"/>
<pinref part="U$6" gate="G$1" pin="P6"/>
</segment>
<segment>
<pinref part="CN1" gate="G$1" pin="2"/>
<wire x1="200.66" y1="137.16" x2="193.04" y2="137.16" width="0.1524" layer="91"/>
<label x="193.04" y="137.16" size="1.778" layer="95" rot="MR0" xref="yes"/>
</segment>
<segment>
<wire x1="200.66" y1="116.84" x2="193.04" y2="116.84" width="0.1524" layer="91"/>
<label x="193.04" y="116.84" size="1.778" layer="95" rot="MR0" xref="yes"/>
<pinref part="CN2" gate="G$1" pin="2"/>
</segment>
</net>
<net name="CANH" class="0">
<segment>
<pinref part="U$1" gate="G$1" pin="P7"/>
<wire x1="10.16" y1="124.46" x2="12.7" y2="124.46" width="0.1524" layer="91"/>
<label x="12.7" y="124.46" size="1.778" layer="95" xref="yes"/>
</segment>
<segment>
<wire x1="38.1" y1="124.46" x2="40.64" y2="124.46" width="0.1524" layer="91"/>
<label x="40.64" y="124.46" size="1.778" layer="95" xref="yes"/>
<pinref part="U$2" gate="G$1" pin="P7"/>
</segment>
<segment>
<wire x1="66.04" y1="124.46" x2="68.58" y2="124.46" width="0.1524" layer="91"/>
<label x="68.58" y="124.46" size="1.778" layer="95" xref="yes"/>
<pinref part="U$3" gate="G$1" pin="P7"/>
</segment>
<segment>
<wire x1="93.98" y1="124.46" x2="96.52" y2="124.46" width="0.1524" layer="91"/>
<label x="96.52" y="124.46" size="1.778" layer="95" xref="yes"/>
<pinref part="U$4" gate="G$1" pin="P7"/>
</segment>
<segment>
<wire x1="121.92" y1="124.46" x2="124.46" y2="124.46" width="0.1524" layer="91"/>
<label x="124.46" y="124.46" size="1.778" layer="95" xref="yes"/>
<pinref part="U$5" gate="G$1" pin="P7"/>
</segment>
<segment>
<wire x1="149.86" y1="124.46" x2="152.4" y2="124.46" width="0.1524" layer="91"/>
<label x="152.4" y="124.46" size="1.778" layer="95" xref="yes"/>
<pinref part="U$6" gate="G$1" pin="P7"/>
</segment>
<segment>
<pinref part="CN1" gate="G$1" pin="3"/>
<wire x1="200.66" y1="134.62" x2="193.04" y2="134.62" width="0.1524" layer="91"/>
<label x="193.04" y="134.62" size="1.778" layer="95" rot="MR0" xref="yes"/>
</segment>
<segment>
<wire x1="200.66" y1="114.3" x2="193.04" y2="114.3" width="0.1524" layer="91"/>
<label x="193.04" y="114.3" size="1.778" layer="95" rot="MR0" xref="yes"/>
<pinref part="CN2" gate="G$1" pin="3"/>
</segment>
</net>
<net name="N$11" class="0">
<segment>
<wire x1="10.16" y1="116.84" x2="12.7" y2="116.84" width="0.1524" layer="91"/>
<pinref part="U$1" gate="G$1" pin="P10"/>
</segment>
</net>
<net name="N$12" class="0">
<segment>
<wire x1="10.16" y1="114.3" x2="12.7" y2="114.3" width="0.1524" layer="91"/>
<pinref part="U$1" gate="G$1" pin="P11"/>
</segment>
</net>
<net name="N$13" class="0">
<segment>
<wire x1="10.16" y1="111.76" x2="12.7" y2="111.76" width="0.1524" layer="91"/>
<pinref part="U$1" gate="G$1" pin="P12"/>
</segment>
</net>
<net name="N$14" class="0">
<segment>
<wire x1="10.16" y1="109.22" x2="12.7" y2="109.22" width="0.1524" layer="91"/>
<pinref part="U$1" gate="G$1" pin="P13"/>
</segment>
</net>
<net name="N$15" class="0">
<segment>
<wire x1="10.16" y1="106.68" x2="12.7" y2="106.68" width="0.1524" layer="91"/>
<pinref part="U$1" gate="G$1" pin="P14"/>
</segment>
</net>
<net name="N$16" class="0">
<segment>
<wire x1="10.16" y1="104.14" x2="12.7" y2="104.14" width="0.1524" layer="91"/>
<pinref part="U$1" gate="G$1" pin="P15"/>
</segment>
</net>
<net name="A01" class="0">
<segment>
<wire x1="10.16" y1="101.6" x2="12.7" y2="101.6" width="0.1524" layer="91"/>
<pinref part="U$1" gate="G$1" pin="P16"/>
<label x="12.7" y="101.6" size="1.778" layer="95" xref="yes"/>
</segment>
<segment>
<pinref part="U$8" gate="G$1" pin="A16"/>
<wire x1="7.62" y1="5.08" x2="7.62" y2="2.54" width="0.1524" layer="91"/>
<label x="7.62" y="2.54" size="1.778" layer="95" rot="R270" xref="yes"/>
</segment>
</net>
<net name="A02" class="0">
<segment>
<pinref part="U$1" gate="G$1" pin="P17"/>
<wire x1="10.16" y1="99.06" x2="12.7" y2="99.06" width="0.1524" layer="91"/>
<label x="12.7" y="99.06" size="1.778" layer="95" xref="yes"/>
</segment>
<segment>
<pinref part="U$8" gate="G$1" pin="A17"/>
<wire x1="10.16" y1="5.08" x2="10.16" y2="2.54" width="0.1524" layer="91"/>
<label x="10.16" y="2.54" size="1.778" layer="95" rot="R270" xref="yes"/>
</segment>
</net>
<net name="A03" class="0">
<segment>
<wire x1="10.16" y1="96.52" x2="12.7" y2="96.52" width="0.1524" layer="91"/>
<pinref part="U$1" gate="G$1" pin="P18"/>
<label x="12.7" y="96.52" size="1.778" layer="95" xref="yes"/>
</segment>
<segment>
<pinref part="U$8" gate="G$1" pin="A18"/>
<wire x1="12.7" y1="5.08" x2="12.7" y2="2.54" width="0.1524" layer="91"/>
<label x="12.7" y="2.54" size="1.778" layer="95" rot="R270" xref="yes"/>
</segment>
</net>
<net name="A04" class="0">
<segment>
<wire x1="10.16" y1="93.98" x2="12.7" y2="93.98" width="0.1524" layer="91"/>
<pinref part="U$1" gate="G$1" pin="P19"/>
<label x="12.7" y="93.98" size="1.778" layer="95" xref="yes"/>
</segment>
<segment>
<pinref part="U$8" gate="G$1" pin="A19"/>
<wire x1="15.24" y1="5.08" x2="15.24" y2="2.54" width="0.1524" layer="91"/>
<label x="15.24" y="2.54" size="1.778" layer="95" rot="R270" xref="yes"/>
</segment>
</net>
<net name="A05" class="0">
<segment>
<wire x1="10.16" y1="91.44" x2="12.7" y2="91.44" width="0.1524" layer="91"/>
<pinref part="U$1" gate="G$1" pin="P20"/>
<label x="12.7" y="91.44" size="1.778" layer="95" xref="yes"/>
</segment>
<segment>
<pinref part="U$8" gate="G$1" pin="A20"/>
<wire x1="17.78" y1="2.54" x2="17.78" y2="5.08" width="0.1524" layer="91"/>
<label x="17.78" y="2.54" size="1.778" layer="95" rot="R270" xref="yes"/>
</segment>
</net>
<net name="A06" class="0">
<segment>
<wire x1="10.16" y1="88.9" x2="12.7" y2="88.9" width="0.1524" layer="91"/>
<pinref part="U$1" gate="G$1" pin="P21"/>
<label x="12.7" y="88.9" size="1.778" layer="95" xref="yes"/>
</segment>
<segment>
<wire x1="20.32" y1="5.08" x2="20.32" y2="2.54" width="0.1524" layer="91"/>
<pinref part="U$8" gate="G$1" pin="A21"/>
<label x="20.32" y="2.54" size="1.778" layer="95" rot="R270" xref="yes"/>
</segment>
</net>
<net name="A07" class="0">
<segment>
<pinref part="U$1" gate="G$1" pin="P22"/>
<wire x1="10.16" y1="86.36" x2="12.7" y2="86.36" width="0.1524" layer="91"/>
<label x="12.7" y="86.36" size="1.778" layer="95" xref="yes"/>
</segment>
<segment>
<wire x1="22.86" y1="5.08" x2="22.86" y2="2.54" width="0.1524" layer="91"/>
<pinref part="U$8" gate="G$1" pin="A22"/>
<label x="22.86" y="2.54" size="1.778" layer="95" rot="R270" xref="yes"/>
</segment>
</net>
<net name="A08" class="0">
<segment>
<wire x1="7.62" y1="33.02" x2="7.62" y2="35.56" width="0.1524" layer="91"/>
<pinref part="U$8" gate="G$1" pin="B16"/>
<label x="7.62" y="35.56" size="1.778" layer="95" rot="R90" xref="yes"/>
</segment>
<segment>
<pinref part="U$1" gate="G$1" pin="P23"/>
<wire x1="10.16" y1="83.82" x2="12.7" y2="83.82" width="0.1524" layer="91"/>
<label x="12.7" y="83.82" size="1.778" layer="95" xref="yes"/>
</segment>
</net>
<net name="A09" class="0">
<segment>
<wire x1="10.16" y1="33.02" x2="10.16" y2="35.56" width="0.1524" layer="91"/>
<pinref part="U$8" gate="G$1" pin="B17"/>
<label x="10.16" y="35.56" size="1.778" layer="95" rot="R90" xref="yes"/>
</segment>
<segment>
<pinref part="U$1" gate="G$1" pin="P24"/>
<wire x1="10.16" y1="81.28" x2="12.7" y2="81.28" width="0.1524" layer="91"/>
<label x="12.7" y="81.28" size="1.778" layer="95" xref="yes"/>
</segment>
</net>
<net name="A10" class="0">
<segment>
<wire x1="12.7" y1="33.02" x2="12.7" y2="35.56" width="0.1524" layer="91"/>
<pinref part="U$8" gate="G$1" pin="B18"/>
<label x="12.7" y="35.56" size="1.778" layer="95" rot="R90" xref="yes"/>
</segment>
<segment>
<pinref part="U$1" gate="G$1" pin="P25"/>
<wire x1="10.16" y1="78.74" x2="12.7" y2="78.74" width="0.1524" layer="91"/>
<label x="12.7" y="78.74" size="1.778" layer="95" xref="yes"/>
</segment>
</net>
<net name="A11" class="0">
<segment>
<wire x1="10.16" y1="76.2" x2="12.7" y2="76.2" width="0.1524" layer="91"/>
<pinref part="U$1" gate="G$1" pin="P26"/>
<label x="12.7" y="76.2" size="1.778" layer="95" xref="yes"/>
</segment>
<segment>
<wire x1="15.24" y1="33.02" x2="15.24" y2="35.56" width="0.1524" layer="91"/>
<pinref part="U$8" gate="G$1" pin="B19"/>
<label x="15.24" y="35.56" size="1.778" layer="95" rot="R90" xref="yes"/>
</segment>
</net>
<net name="A12" class="0">
<segment>
<wire x1="10.16" y1="73.66" x2="12.7" y2="73.66" width="0.1524" layer="91"/>
<pinref part="U$1" gate="G$1" pin="P27"/>
<label x="12.7" y="73.66" size="1.778" layer="95" xref="yes"/>
</segment>
<segment>
<wire x1="17.78" y1="33.02" x2="17.78" y2="35.56" width="0.1524" layer="91"/>
<pinref part="U$8" gate="G$1" pin="B20"/>
<label x="17.78" y="35.56" size="1.778" layer="95" rot="R90" xref="yes"/>
</segment>
</net>
<net name="A13" class="0">
<segment>
<wire x1="10.16" y1="71.12" x2="12.7" y2="71.12" width="0.1524" layer="91"/>
<pinref part="U$1" gate="G$1" pin="P28"/>
<label x="12.7" y="71.12" size="1.778" layer="95" xref="yes"/>
</segment>
<segment>
<wire x1="20.32" y1="33.02" x2="20.32" y2="35.56" width="0.1524" layer="91"/>
<pinref part="U$8" gate="G$1" pin="B21"/>
<label x="20.32" y="35.56" size="1.778" layer="95" rot="R90" xref="yes"/>
</segment>
</net>
<net name="A14" class="0">
<segment>
<wire x1="10.16" y1="68.58" x2="12.7" y2="68.58" width="0.1524" layer="91"/>
<pinref part="U$1" gate="G$1" pin="P29"/>
<label x="12.7" y="68.58" size="1.778" layer="95" xref="yes"/>
</segment>
<segment>
<wire x1="22.86" y1="33.02" x2="22.86" y2="35.56" width="0.1524" layer="91"/>
<pinref part="U$8" gate="G$1" pin="B22"/>
<label x="22.86" y="35.56" size="1.778" layer="95" rot="R90" xref="yes"/>
</segment>
</net>
<net name="A15" class="0">
<segment>
<wire x1="10.16" y1="66.04" x2="12.7" y2="66.04" width="0.1524" layer="91"/>
<pinref part="U$1" gate="G$1" pin="P30"/>
<label x="12.7" y="66.04" size="1.778" layer="95" xref="yes"/>
</segment>
<segment>
<wire x1="25.4" y1="33.02" x2="25.4" y2="35.56" width="0.1524" layer="91"/>
<pinref part="U$8" gate="G$1" pin="B23"/>
<label x="25.4" y="35.56" size="1.778" layer="95" rot="R90" xref="yes"/>
</segment>
</net>
<net name="N$3" class="0">
<segment>
<wire x1="38.1" y1="116.84" x2="40.64" y2="116.84" width="0.1524" layer="91"/>
<pinref part="U$2" gate="G$1" pin="P10"/>
</segment>
</net>
<net name="N$4" class="0">
<segment>
<wire x1="38.1" y1="114.3" x2="40.64" y2="114.3" width="0.1524" layer="91"/>
<pinref part="U$2" gate="G$1" pin="P11"/>
</segment>
</net>
<net name="N$5" class="0">
<segment>
<wire x1="38.1" y1="111.76" x2="40.64" y2="111.76" width="0.1524" layer="91"/>
<pinref part="U$2" gate="G$1" pin="P12"/>
</segment>
</net>
<net name="N$6" class="0">
<segment>
<wire x1="38.1" y1="109.22" x2="40.64" y2="109.22" width="0.1524" layer="91"/>
<pinref part="U$2" gate="G$1" pin="P13"/>
</segment>
</net>
<net name="N$7" class="0">
<segment>
<wire x1="38.1" y1="106.68" x2="40.64" y2="106.68" width="0.1524" layer="91"/>
<pinref part="U$2" gate="G$1" pin="P14"/>
</segment>
</net>
<net name="N$8" class="0">
<segment>
<wire x1="38.1" y1="104.14" x2="40.64" y2="104.14" width="0.1524" layer="91"/>
<pinref part="U$2" gate="G$1" pin="P15"/>
</segment>
</net>
<net name="B08" class="0">
<segment>
<wire x1="38.1" y1="83.82" x2="40.64" y2="83.82" width="0.1524" layer="91"/>
<pinref part="U$2" gate="G$1" pin="P23"/>
<label x="40.64" y="83.82" size="1.778" layer="95" xref="yes"/>
</segment>
<segment>
<wire x1="33.02" y1="33.02" x2="33.02" y2="35.56" width="0.1524" layer="91"/>
<pinref part="U$8" gate="G$1" pin="B26"/>
<label x="33.02" y="35.56" size="1.778" layer="95" rot="R90" xref="yes"/>
</segment>
</net>
<net name="B09" class="0">
<segment>
<wire x1="38.1" y1="81.28" x2="40.64" y2="81.28" width="0.1524" layer="91"/>
<pinref part="U$2" gate="G$1" pin="P24"/>
<label x="40.64" y="81.28" size="1.778" layer="95" xref="yes"/>
</segment>
<segment>
<wire x1="35.56" y1="33.02" x2="35.56" y2="35.56" width="0.1524" layer="91"/>
<pinref part="U$8" gate="G$1" pin="B27"/>
<label x="35.56" y="35.56" size="1.778" layer="95" rot="R90" xref="yes"/>
</segment>
</net>
<net name="B10" class="0">
<segment>
<wire x1="38.1" y1="78.74" x2="40.64" y2="78.74" width="0.1524" layer="91"/>
<pinref part="U$2" gate="G$1" pin="P25"/>
<label x="40.64" y="78.74" size="1.778" layer="95" xref="yes"/>
</segment>
<segment>
<wire x1="38.1" y1="33.02" x2="38.1" y2="35.56" width="0.1524" layer="91"/>
<pinref part="U$8" gate="G$1" pin="B28"/>
<label x="38.1" y="35.56" size="1.778" layer="95" rot="R90" xref="yes"/>
</segment>
</net>
<net name="B11" class="0">
<segment>
<wire x1="38.1" y1="76.2" x2="40.64" y2="76.2" width="0.1524" layer="91"/>
<pinref part="U$2" gate="G$1" pin="P26"/>
<label x="40.64" y="76.2" size="1.778" layer="95" xref="yes"/>
</segment>
<segment>
<wire x1="40.64" y1="33.02" x2="40.64" y2="35.56" width="0.1524" layer="91"/>
<pinref part="U$8" gate="G$1" pin="B29"/>
<label x="40.64" y="35.56" size="1.778" layer="95" rot="R90" xref="yes"/>
</segment>
</net>
<net name="B12" class="0">
<segment>
<wire x1="38.1" y1="73.66" x2="40.64" y2="73.66" width="0.1524" layer="91"/>
<pinref part="U$2" gate="G$1" pin="P27"/>
<label x="40.64" y="73.66" size="1.778" layer="95" xref="yes"/>
</segment>
<segment>
<wire x1="43.18" y1="33.02" x2="43.18" y2="35.56" width="0.1524" layer="91"/>
<pinref part="U$8" gate="G$1" pin="B30"/>
<label x="43.18" y="35.56" size="1.778" layer="95" rot="R90" xref="yes"/>
</segment>
</net>
<net name="B13" class="0">
<segment>
<wire x1="38.1" y1="71.12" x2="40.64" y2="71.12" width="0.1524" layer="91"/>
<pinref part="U$2" gate="G$1" pin="P28"/>
<label x="40.64" y="71.12" size="1.778" layer="95" xref="yes"/>
</segment>
<segment>
<wire x1="45.72" y1="33.02" x2="45.72" y2="35.56" width="0.1524" layer="91"/>
<pinref part="U$8" gate="G$1" pin="B31"/>
<label x="45.72" y="35.56" size="1.778" layer="95" rot="R90" xref="yes"/>
</segment>
</net>
<net name="B14" class="0">
<segment>
<wire x1="38.1" y1="68.58" x2="40.64" y2="68.58" width="0.1524" layer="91"/>
<pinref part="U$2" gate="G$1" pin="P29"/>
<label x="40.64" y="68.58" size="1.778" layer="95" xref="yes"/>
</segment>
<segment>
<wire x1="48.26" y1="33.02" x2="48.26" y2="35.56" width="0.1524" layer="91"/>
<pinref part="U$8" gate="G$1" pin="B32"/>
<label x="48.26" y="35.56" size="1.778" layer="95" rot="R90" xref="yes"/>
</segment>
</net>
<net name="B15" class="0">
<segment>
<wire x1="38.1" y1="66.04" x2="40.64" y2="66.04" width="0.1524" layer="91"/>
<pinref part="U$2" gate="G$1" pin="P30"/>
<label x="40.64" y="66.04" size="1.778" layer="95" xref="yes"/>
</segment>
<segment>
<wire x1="50.8" y1="33.02" x2="50.8" y2="35.56" width="0.1524" layer="91"/>
<pinref part="U$8" gate="G$1" pin="B33"/>
<label x="50.8" y="35.56" size="1.778" layer="95" rot="R90" xref="yes"/>
</segment>
</net>
<net name="N$60" class="0">
<segment>
<wire x1="66.04" y1="116.84" x2="68.58" y2="116.84" width="0.1524" layer="91"/>
<pinref part="U$3" gate="G$1" pin="P10"/>
</segment>
</net>
<net name="N$61" class="0">
<segment>
<wire x1="66.04" y1="114.3" x2="68.58" y2="114.3" width="0.1524" layer="91"/>
<pinref part="U$3" gate="G$1" pin="P11"/>
</segment>
</net>
<net name="N$62" class="0">
<segment>
<wire x1="66.04" y1="111.76" x2="68.58" y2="111.76" width="0.1524" layer="91"/>
<pinref part="U$3" gate="G$1" pin="P12"/>
</segment>
</net>
<net name="N$63" class="0">
<segment>
<wire x1="66.04" y1="109.22" x2="68.58" y2="109.22" width="0.1524" layer="91"/>
<pinref part="U$3" gate="G$1" pin="P13"/>
</segment>
</net>
<net name="N$64" class="0">
<segment>
<wire x1="66.04" y1="106.68" x2="68.58" y2="106.68" width="0.1524" layer="91"/>
<pinref part="U$3" gate="G$1" pin="P14"/>
</segment>
</net>
<net name="N$65" class="0">
<segment>
<wire x1="66.04" y1="104.14" x2="68.58" y2="104.14" width="0.1524" layer="91"/>
<pinref part="U$3" gate="G$1" pin="P15"/>
</segment>
</net>
<net name="C01" class="0">
<segment>
<wire x1="66.04" y1="101.6" x2="68.58" y2="101.6" width="0.1524" layer="91"/>
<pinref part="U$3" gate="G$1" pin="P16"/>
<label x="68.58" y="101.6" size="1.778" layer="95" xref="yes"/>
</segment>
<segment>
<wire x1="58.42" y1="5.08" x2="58.42" y2="2.54" width="0.1524" layer="91"/>
<pinref part="U$8" gate="G$1" pin="A36"/>
<label x="58.42" y="2.54" size="1.778" layer="95" rot="R270" xref="yes"/>
</segment>
</net>
<net name="C02" class="0">
<segment>
<wire x1="66.04" y1="99.06" x2="68.58" y2="99.06" width="0.1524" layer="91"/>
<pinref part="U$3" gate="G$1" pin="P17"/>
<label x="68.58" y="99.06" size="1.778" layer="95" xref="yes"/>
</segment>
<segment>
<wire x1="60.96" y1="5.08" x2="60.96" y2="2.54" width="0.1524" layer="91"/>
<pinref part="U$8" gate="G$1" pin="A37"/>
<label x="60.96" y="2.54" size="1.778" layer="95" rot="R270" xref="yes"/>
</segment>
</net>
<net name="C03" class="0">
<segment>
<wire x1="66.04" y1="96.52" x2="68.58" y2="96.52" width="0.1524" layer="91"/>
<pinref part="U$3" gate="G$1" pin="P18"/>
<label x="68.58" y="96.52" size="1.778" layer="95" xref="yes"/>
</segment>
<segment>
<wire x1="63.5" y1="2.54" x2="63.5" y2="5.08" width="0.1524" layer="91"/>
<pinref part="U$8" gate="G$1" pin="A38"/>
<label x="63.5" y="2.54" size="1.778" layer="95" rot="R270" xref="yes"/>
</segment>
</net>
<net name="C04" class="0">
<segment>
<wire x1="66.04" y1="93.98" x2="68.58" y2="93.98" width="0.1524" layer="91"/>
<pinref part="U$3" gate="G$1" pin="P19"/>
<label x="68.58" y="93.98" size="1.778" layer="95" xref="yes"/>
</segment>
<segment>
<wire x1="66.04" y1="5.08" x2="66.04" y2="2.54" width="0.1524" layer="91"/>
<pinref part="U$8" gate="G$1" pin="A39"/>
<label x="66.04" y="2.54" size="1.778" layer="95" rot="R270" xref="yes"/>
</segment>
</net>
<net name="C05" class="0">
<segment>
<wire x1="66.04" y1="91.44" x2="68.58" y2="91.44" width="0.1524" layer="91"/>
<pinref part="U$3" gate="G$1" pin="P20"/>
<label x="68.58" y="91.44" size="1.778" layer="95" xref="yes"/>
</segment>
<segment>
<wire x1="68.58" y1="5.08" x2="68.58" y2="2.54" width="0.1524" layer="91"/>
<pinref part="U$8" gate="G$1" pin="A40"/>
<label x="68.58" y="2.54" size="1.778" layer="95" rot="R270" xref="yes"/>
</segment>
</net>
<net name="C06" class="0">
<segment>
<wire x1="66.04" y1="88.9" x2="68.58" y2="88.9" width="0.1524" layer="91"/>
<pinref part="U$3" gate="G$1" pin="P21"/>
<label x="68.58" y="88.9" size="1.778" layer="95" xref="yes"/>
</segment>
<segment>
<wire x1="71.12" y1="5.08" x2="71.12" y2="2.54" width="0.1524" layer="91"/>
<pinref part="U$8" gate="G$1" pin="A41"/>
<label x="71.12" y="2.54" size="1.778" layer="95" rot="R270" xref="yes"/>
</segment>
</net>
<net name="C07" class="0">
<segment>
<wire x1="66.04" y1="86.36" x2="68.58" y2="86.36" width="0.1524" layer="91"/>
<pinref part="U$3" gate="G$1" pin="P22"/>
<label x="68.58" y="86.36" size="1.778" layer="95" xref="yes"/>
</segment>
<segment>
<wire x1="73.66" y1="5.08" x2="73.66" y2="2.54" width="0.1524" layer="91"/>
<pinref part="U$8" gate="G$1" pin="A42"/>
<label x="73.66" y="2.54" size="1.778" layer="95" rot="R270" xref="yes"/>
</segment>
</net>
<net name="C08" class="0">
<segment>
<wire x1="66.04" y1="83.82" x2="68.58" y2="83.82" width="0.1524" layer="91"/>
<pinref part="U$3" gate="G$1" pin="P23"/>
<label x="68.58" y="83.82" size="1.778" layer="95" xref="yes"/>
</segment>
<segment>
<wire x1="58.42" y1="33.02" x2="58.42" y2="35.56" width="0.1524" layer="91"/>
<pinref part="U$8" gate="G$1" pin="B36"/>
<label x="58.42" y="35.56" size="1.778" layer="95" rot="R90" xref="yes"/>
</segment>
</net>
<net name="C09" class="0">
<segment>
<wire x1="66.04" y1="81.28" x2="68.58" y2="81.28" width="0.1524" layer="91"/>
<pinref part="U$3" gate="G$1" pin="P24"/>
<label x="68.58" y="81.28" size="1.778" layer="95" xref="yes"/>
</segment>
<segment>
<wire x1="60.96" y1="33.02" x2="60.96" y2="35.56" width="0.1524" layer="91"/>
<pinref part="U$8" gate="G$1" pin="B37"/>
<label x="60.96" y="35.56" size="1.778" layer="95" rot="R90" xref="yes"/>
</segment>
</net>
<net name="C10" class="0">
<segment>
<wire x1="66.04" y1="78.74" x2="68.58" y2="78.74" width="0.1524" layer="91"/>
<pinref part="U$3" gate="G$1" pin="P25"/>
<label x="68.58" y="78.74" size="1.778" layer="95" xref="yes"/>
</segment>
<segment>
<wire x1="63.5" y1="33.02" x2="63.5" y2="35.56" width="0.1524" layer="91"/>
<pinref part="U$8" gate="G$1" pin="B38"/>
<label x="63.5" y="35.56" size="1.778" layer="95" rot="R90" xref="yes"/>
</segment>
</net>
<net name="C11" class="0">
<segment>
<wire x1="66.04" y1="76.2" x2="68.58" y2="76.2" width="0.1524" layer="91"/>
<pinref part="U$3" gate="G$1" pin="P26"/>
<label x="68.58" y="76.2" size="1.778" layer="95" xref="yes"/>
</segment>
<segment>
<wire x1="66.04" y1="33.02" x2="66.04" y2="35.56" width="0.1524" layer="91"/>
<pinref part="U$8" gate="G$1" pin="B39"/>
<label x="66.04" y="35.56" size="1.778" layer="95" rot="R90" xref="yes"/>
</segment>
</net>
<net name="C12" class="0">
<segment>
<wire x1="66.04" y1="73.66" x2="68.58" y2="73.66" width="0.1524" layer="91"/>
<pinref part="U$3" gate="G$1" pin="P27"/>
<label x="68.58" y="73.66" size="1.778" layer="95" xref="yes"/>
</segment>
<segment>
<wire x1="68.58" y1="33.02" x2="68.58" y2="35.56" width="0.1524" layer="91"/>
<pinref part="U$8" gate="G$1" pin="B40"/>
<label x="68.58" y="35.56" size="1.778" layer="95" rot="R90" xref="yes"/>
</segment>
</net>
<net name="C13" class="0">
<segment>
<wire x1="66.04" y1="71.12" x2="68.58" y2="71.12" width="0.1524" layer="91"/>
<pinref part="U$3" gate="G$1" pin="P28"/>
<label x="68.58" y="71.12" size="1.778" layer="95" xref="yes"/>
</segment>
<segment>
<wire x1="71.12" y1="33.02" x2="71.12" y2="35.56" width="0.1524" layer="91"/>
<pinref part="U$8" gate="G$1" pin="B41"/>
<label x="71.12" y="35.56" size="1.778" layer="95" rot="R90" xref="yes"/>
</segment>
</net>
<net name="C14" class="0">
<segment>
<wire x1="66.04" y1="68.58" x2="68.58" y2="68.58" width="0.1524" layer="91"/>
<pinref part="U$3" gate="G$1" pin="P29"/>
<label x="68.58" y="68.58" size="1.778" layer="95" xref="yes"/>
</segment>
<segment>
<wire x1="73.66" y1="33.02" x2="73.66" y2="35.56" width="0.1524" layer="91"/>
<pinref part="U$8" gate="G$1" pin="B42"/>
<label x="73.66" y="35.56" size="1.778" layer="95" rot="R90" xref="yes"/>
</segment>
</net>
<net name="C15" class="0">
<segment>
<wire x1="66.04" y1="66.04" x2="68.58" y2="66.04" width="0.1524" layer="91"/>
<pinref part="U$3" gate="G$1" pin="P30"/>
<label x="68.58" y="66.04" size="1.778" layer="95" xref="yes"/>
</segment>
<segment>
<wire x1="76.2" y1="33.02" x2="76.2" y2="35.56" width="0.1524" layer="91"/>
<pinref part="U$8" gate="G$1" pin="B43"/>
<label x="76.2" y="35.56" size="1.778" layer="95" rot="R90" xref="yes"/>
</segment>
</net>
<net name="N$89" class="0">
<segment>
<wire x1="93.98" y1="116.84" x2="96.52" y2="116.84" width="0.1524" layer="91"/>
<pinref part="U$4" gate="G$1" pin="P10"/>
</segment>
</net>
<net name="N$90" class="0">
<segment>
<wire x1="93.98" y1="114.3" x2="96.52" y2="114.3" width="0.1524" layer="91"/>
<pinref part="U$4" gate="G$1" pin="P11"/>
</segment>
</net>
<net name="N$91" class="0">
<segment>
<wire x1="93.98" y1="111.76" x2="96.52" y2="111.76" width="0.1524" layer="91"/>
<pinref part="U$4" gate="G$1" pin="P12"/>
</segment>
</net>
<net name="N$92" class="0">
<segment>
<wire x1="93.98" y1="109.22" x2="96.52" y2="109.22" width="0.1524" layer="91"/>
<pinref part="U$4" gate="G$1" pin="P13"/>
</segment>
</net>
<net name="N$93" class="0">
<segment>
<wire x1="93.98" y1="106.68" x2="96.52" y2="106.68" width="0.1524" layer="91"/>
<pinref part="U$4" gate="G$1" pin="P14"/>
</segment>
</net>
<net name="N$94" class="0">
<segment>
<wire x1="93.98" y1="104.14" x2="96.52" y2="104.14" width="0.1524" layer="91"/>
<pinref part="U$4" gate="G$1" pin="P15"/>
</segment>
</net>
<net name="D01" class="0">
<segment>
<wire x1="93.98" y1="101.6" x2="96.52" y2="101.6" width="0.1524" layer="91"/>
<pinref part="U$4" gate="G$1" pin="P16"/>
<label x="96.52" y="101.6" size="1.778" layer="95" xref="yes"/>
</segment>
<segment>
<wire x1="83.82" y1="5.08" x2="83.82" y2="2.54" width="0.1524" layer="91"/>
<pinref part="U$8" gate="G$1" pin="A46"/>
<label x="83.82" y="2.54" size="1.778" layer="95" rot="R270" xref="yes"/>
</segment>
</net>
<net name="D02" class="0">
<segment>
<wire x1="93.98" y1="99.06" x2="96.52" y2="99.06" width="0.1524" layer="91"/>
<pinref part="U$4" gate="G$1" pin="P17"/>
<label x="96.52" y="99.06" size="1.778" layer="95" xref="yes"/>
</segment>
<segment>
<wire x1="86.36" y1="2.54" x2="86.36" y2="5.08" width="0.1524" layer="91"/>
<pinref part="U$8" gate="G$1" pin="A47"/>
<label x="86.36" y="2.54" size="1.778" layer="95" rot="R270" xref="yes"/>
</segment>
</net>
<net name="D03" class="0">
<segment>
<wire x1="93.98" y1="96.52" x2="96.52" y2="96.52" width="0.1524" layer="91"/>
<pinref part="U$4" gate="G$1" pin="P18"/>
<label x="96.52" y="96.52" size="1.778" layer="95" xref="yes"/>
</segment>
<segment>
<wire x1="88.9" y1="5.08" x2="88.9" y2="2.54" width="0.1524" layer="91"/>
<pinref part="U$8" gate="G$1" pin="A48"/>
<label x="88.9" y="2.54" size="1.778" layer="95" rot="R270" xref="yes"/>
</segment>
</net>
<net name="D04" class="0">
<segment>
<wire x1="93.98" y1="93.98" x2="96.52" y2="93.98" width="0.1524" layer="91"/>
<pinref part="U$4" gate="G$1" pin="P19"/>
<label x="96.52" y="93.98" size="1.778" layer="95" xref="yes"/>
</segment>
<segment>
<wire x1="91.44" y1="5.08" x2="91.44" y2="2.54" width="0.1524" layer="91"/>
<pinref part="U$8" gate="G$1" pin="A49"/>
<label x="91.44" y="2.54" size="1.778" layer="95" rot="R270" xref="yes"/>
</segment>
</net>
<net name="D05" class="0">
<segment>
<wire x1="93.98" y1="91.44" x2="96.52" y2="91.44" width="0.1524" layer="91"/>
<pinref part="U$4" gate="G$1" pin="P20"/>
<label x="96.52" y="91.44" size="1.778" layer="95" xref="yes"/>
</segment>
<segment>
<wire x1="93.98" y1="5.08" x2="93.98" y2="2.54" width="0.1524" layer="91"/>
<pinref part="U$8" gate="G$1" pin="A50"/>
<label x="93.98" y="2.54" size="1.778" layer="95" rot="R270" xref="yes"/>
</segment>
</net>
<net name="D06" class="0">
<segment>
<wire x1="93.98" y1="88.9" x2="96.52" y2="88.9" width="0.1524" layer="91"/>
<pinref part="U$4" gate="G$1" pin="P21"/>
<label x="96.52" y="88.9" size="1.778" layer="95" xref="yes"/>
</segment>
<segment>
<wire x1="96.52" y1="5.08" x2="96.52" y2="2.54" width="0.1524" layer="91"/>
<pinref part="U$8" gate="G$1" pin="A51"/>
<label x="96.52" y="2.54" size="1.778" layer="95" rot="R270" xref="yes"/>
</segment>
</net>
<net name="D07" class="0">
<segment>
<wire x1="93.98" y1="86.36" x2="96.52" y2="86.36" width="0.1524" layer="91"/>
<pinref part="U$4" gate="G$1" pin="P22"/>
<label x="96.52" y="86.36" size="1.778" layer="95" xref="yes"/>
</segment>
<segment>
<wire x1="99.06" y1="5.08" x2="99.06" y2="2.54" width="0.1524" layer="91"/>
<pinref part="U$8" gate="G$1" pin="A52"/>
<label x="99.06" y="2.54" size="1.778" layer="95" rot="R270" xref="yes"/>
</segment>
</net>
<net name="D08" class="0">
<segment>
<wire x1="93.98" y1="83.82" x2="96.52" y2="83.82" width="0.1524" layer="91"/>
<pinref part="U$4" gate="G$1" pin="P23"/>
<label x="96.52" y="83.82" size="1.778" layer="95" xref="yes"/>
</segment>
<segment>
<wire x1="83.82" y1="33.02" x2="83.82" y2="35.56" width="0.1524" layer="91"/>
<pinref part="U$8" gate="G$1" pin="B46"/>
<label x="83.82" y="35.56" size="1.778" layer="95" rot="R90" xref="yes"/>
</segment>
</net>
<net name="D09" class="0">
<segment>
<wire x1="93.98" y1="81.28" x2="96.52" y2="81.28" width="0.1524" layer="91"/>
<pinref part="U$4" gate="G$1" pin="P24"/>
<label x="96.52" y="81.28" size="1.778" layer="95" xref="yes"/>
</segment>
<segment>
<wire x1="86.36" y1="33.02" x2="86.36" y2="35.56" width="0.1524" layer="91"/>
<pinref part="U$8" gate="G$1" pin="B47"/>
<label x="86.36" y="35.56" size="1.778" layer="95" rot="R90" xref="yes"/>
</segment>
</net>
<net name="D10" class="0">
<segment>
<wire x1="93.98" y1="78.74" x2="96.52" y2="78.74" width="0.1524" layer="91"/>
<pinref part="U$4" gate="G$1" pin="P25"/>
<label x="96.52" y="78.74" size="1.778" layer="95" xref="yes"/>
</segment>
<segment>
<wire x1="88.9" y1="33.02" x2="88.9" y2="35.56" width="0.1524" layer="91"/>
<pinref part="U$8" gate="G$1" pin="B48"/>
<label x="88.9" y="35.56" size="1.778" layer="95" rot="R90" xref="yes"/>
</segment>
</net>
<net name="D11" class="0">
<segment>
<wire x1="93.98" y1="76.2" x2="96.52" y2="76.2" width="0.1524" layer="91"/>
<pinref part="U$4" gate="G$1" pin="P26"/>
<label x="96.52" y="76.2" size="1.778" layer="95" xref="yes"/>
</segment>
<segment>
<wire x1="91.44" y1="33.02" x2="91.44" y2="35.56" width="0.1524" layer="91"/>
<pinref part="U$8" gate="G$1" pin="B49"/>
<label x="91.44" y="35.56" size="1.778" layer="95" rot="R90" xref="yes"/>
</segment>
</net>
<net name="D12" class="0">
<segment>
<wire x1="93.98" y1="73.66" x2="96.52" y2="73.66" width="0.1524" layer="91"/>
<pinref part="U$4" gate="G$1" pin="P27"/>
<label x="96.52" y="73.66" size="1.778" layer="95" xref="yes"/>
</segment>
<segment>
<wire x1="93.98" y1="33.02" x2="93.98" y2="35.56" width="0.1524" layer="91"/>
<pinref part="U$8" gate="G$1" pin="B50"/>
<label x="93.98" y="35.56" size="1.778" layer="95" rot="R90" xref="yes"/>
</segment>
</net>
<net name="D13" class="0">
<segment>
<wire x1="93.98" y1="71.12" x2="96.52" y2="71.12" width="0.1524" layer="91"/>
<pinref part="U$4" gate="G$1" pin="P28"/>
<label x="96.52" y="71.12" size="1.778" layer="95" xref="yes"/>
</segment>
<segment>
<wire x1="96.52" y1="33.02" x2="96.52" y2="35.56" width="0.1524" layer="91"/>
<pinref part="U$8" gate="G$1" pin="B51"/>
<label x="96.52" y="35.56" size="1.778" layer="95" rot="R90" xref="yes"/>
</segment>
</net>
<net name="D14" class="0">
<segment>
<wire x1="93.98" y1="68.58" x2="96.52" y2="68.58" width="0.1524" layer="91"/>
<pinref part="U$4" gate="G$1" pin="P29"/>
<label x="96.52" y="68.58" size="1.778" layer="95" xref="yes"/>
</segment>
<segment>
<wire x1="99.06" y1="33.02" x2="99.06" y2="35.56" width="0.1524" layer="91"/>
<pinref part="U$8" gate="G$1" pin="B52"/>
<label x="99.06" y="35.56" size="1.778" layer="95" rot="R90" xref="yes"/>
</segment>
</net>
<net name="D15" class="0">
<segment>
<wire x1="93.98" y1="66.04" x2="96.52" y2="66.04" width="0.1524" layer="91"/>
<pinref part="U$4" gate="G$1" pin="P30"/>
<label x="96.52" y="66.04" size="1.778" layer="95" xref="yes"/>
</segment>
<segment>
<wire x1="101.6" y1="33.02" x2="101.6" y2="35.56" width="0.1524" layer="91"/>
<pinref part="U$8" gate="G$1" pin="B53"/>
<label x="101.6" y="35.56" size="1.778" layer="95" rot="R90" xref="yes"/>
</segment>
</net>
<net name="N$118" class="0">
<segment>
<wire x1="121.92" y1="116.84" x2="124.46" y2="116.84" width="0.1524" layer="91"/>
<pinref part="U$5" gate="G$1" pin="P10"/>
</segment>
</net>
<net name="N$119" class="0">
<segment>
<wire x1="121.92" y1="114.3" x2="124.46" y2="114.3" width="0.1524" layer="91"/>
<pinref part="U$5" gate="G$1" pin="P11"/>
</segment>
</net>
<net name="N$120" class="0">
<segment>
<wire x1="121.92" y1="111.76" x2="124.46" y2="111.76" width="0.1524" layer="91"/>
<pinref part="U$5" gate="G$1" pin="P12"/>
</segment>
</net>
<net name="N$121" class="0">
<segment>
<wire x1="121.92" y1="109.22" x2="124.46" y2="109.22" width="0.1524" layer="91"/>
<pinref part="U$5" gate="G$1" pin="P13"/>
</segment>
</net>
<net name="N$122" class="0">
<segment>
<wire x1="121.92" y1="106.68" x2="124.46" y2="106.68" width="0.1524" layer="91"/>
<pinref part="U$5" gate="G$1" pin="P14"/>
</segment>
</net>
<net name="N$123" class="0">
<segment>
<wire x1="121.92" y1="104.14" x2="124.46" y2="104.14" width="0.1524" layer="91"/>
<pinref part="U$5" gate="G$1" pin="P15"/>
</segment>
</net>
<net name="E01" class="0">
<segment>
<wire x1="121.92" y1="101.6" x2="124.46" y2="101.6" width="0.1524" layer="91"/>
<pinref part="U$5" gate="G$1" pin="P16"/>
<label x="124.46" y="101.6" size="1.778" layer="95" xref="yes"/>
</segment>
<segment>
<wire x1="109.22" y1="2.54" x2="109.22" y2="5.08" width="0.1524" layer="91"/>
<pinref part="U$8" gate="G$1" pin="A56"/>
<label x="109.22" y="2.54" size="1.778" layer="95" rot="R270" xref="yes"/>
</segment>
</net>
<net name="E02" class="0">
<segment>
<wire x1="121.92" y1="99.06" x2="124.46" y2="99.06" width="0.1524" layer="91"/>
<pinref part="U$5" gate="G$1" pin="P17"/>
<label x="124.46" y="99.06" size="1.778" layer="95" xref="yes"/>
</segment>
<segment>
<wire x1="111.76" y1="5.08" x2="111.76" y2="2.54" width="0.1524" layer="91"/>
<pinref part="U$8" gate="G$1" pin="A57"/>
<label x="111.76" y="2.54" size="1.778" layer="95" rot="R270" xref="yes"/>
</segment>
</net>
<net name="E03" class="0">
<segment>
<wire x1="121.92" y1="96.52" x2="124.46" y2="96.52" width="0.1524" layer="91"/>
<pinref part="U$5" gate="G$1" pin="P18"/>
<label x="124.46" y="96.52" size="1.778" layer="95" xref="yes"/>
</segment>
<segment>
<wire x1="114.3" y1="5.08" x2="114.3" y2="2.54" width="0.1524" layer="91"/>
<pinref part="U$8" gate="G$1" pin="A58"/>
<label x="114.3" y="2.54" size="1.778" layer="95" rot="R270" xref="yes"/>
</segment>
</net>
<net name="E04" class="0">
<segment>
<wire x1="121.92" y1="93.98" x2="124.46" y2="93.98" width="0.1524" layer="91"/>
<pinref part="U$5" gate="G$1" pin="P19"/>
<label x="124.46" y="93.98" size="1.778" layer="95" xref="yes"/>
</segment>
<segment>
<wire x1="116.84" y1="5.08" x2="116.84" y2="2.54" width="0.1524" layer="91"/>
<pinref part="U$8" gate="G$1" pin="A59"/>
<label x="116.84" y="2.54" size="1.778" layer="95" rot="R270" xref="yes"/>
</segment>
</net>
<net name="E05" class="0">
<segment>
<wire x1="121.92" y1="91.44" x2="124.46" y2="91.44" width="0.1524" layer="91"/>
<pinref part="U$5" gate="G$1" pin="P20"/>
<label x="124.46" y="91.44" size="1.778" layer="95" xref="yes"/>
</segment>
<segment>
<wire x1="119.38" y1="5.08" x2="119.38" y2="2.54" width="0.1524" layer="91"/>
<pinref part="U$8" gate="G$1" pin="A60"/>
<label x="119.38" y="2.54" size="1.778" layer="95" rot="R270" xref="yes"/>
</segment>
</net>
<net name="E06" class="0">
<segment>
<wire x1="121.92" y1="88.9" x2="124.46" y2="88.9" width="0.1524" layer="91"/>
<pinref part="U$5" gate="G$1" pin="P21"/>
<label x="124.46" y="88.9" size="1.778" layer="95" xref="yes"/>
</segment>
<segment>
<wire x1="121.92" y1="5.08" x2="121.92" y2="2.54" width="0.1524" layer="91"/>
<pinref part="U$8" gate="G$1" pin="A61"/>
<label x="121.92" y="2.54" size="1.778" layer="95" rot="R270" xref="yes"/>
</segment>
</net>
<net name="E07" class="0">
<segment>
<wire x1="121.92" y1="86.36" x2="124.46" y2="86.36" width="0.1524" layer="91"/>
<pinref part="U$5" gate="G$1" pin="P22"/>
<label x="124.46" y="86.36" size="1.778" layer="95" xref="yes"/>
</segment>
<segment>
<wire x1="124.46" y1="5.08" x2="124.46" y2="2.54" width="0.1524" layer="91"/>
<pinref part="U$8" gate="G$1" pin="A62"/>
<label x="124.46" y="2.54" size="1.778" layer="95" rot="R270" xref="yes"/>
</segment>
</net>
<net name="E08" class="0">
<segment>
<wire x1="121.92" y1="83.82" x2="124.46" y2="83.82" width="0.1524" layer="91"/>
<pinref part="U$5" gate="G$1" pin="P23"/>
<label x="124.46" y="83.82" size="1.778" layer="95" xref="yes"/>
</segment>
<segment>
<wire x1="109.22" y1="33.02" x2="109.22" y2="35.56" width="0.1524" layer="91"/>
<pinref part="U$8" gate="G$1" pin="B56"/>
<label x="109.22" y="35.56" size="1.778" layer="95" rot="R90" xref="yes"/>
</segment>
</net>
<net name="E09" class="0">
<segment>
<wire x1="121.92" y1="81.28" x2="124.46" y2="81.28" width="0.1524" layer="91"/>
<pinref part="U$5" gate="G$1" pin="P24"/>
<label x="124.46" y="81.28" size="1.778" layer="95" xref="yes"/>
</segment>
<segment>
<wire x1="111.76" y1="33.02" x2="111.76" y2="35.56" width="0.1524" layer="91"/>
<pinref part="U$8" gate="G$1" pin="B57"/>
<label x="111.76" y="35.56" size="1.778" layer="95" rot="R90" xref="yes"/>
</segment>
</net>
<net name="E10" class="0">
<segment>
<wire x1="121.92" y1="78.74" x2="124.46" y2="78.74" width="0.1524" layer="91"/>
<pinref part="U$5" gate="G$1" pin="P25"/>
<label x="124.46" y="78.74" size="1.778" layer="95" xref="yes"/>
</segment>
<segment>
<wire x1="114.3" y1="33.02" x2="114.3" y2="35.56" width="0.1524" layer="91"/>
<pinref part="U$8" gate="G$1" pin="B58"/>
<label x="114.3" y="35.56" size="1.778" layer="95" rot="R90" xref="yes"/>
</segment>
</net>
<net name="E11" class="0">
<segment>
<wire x1="121.92" y1="76.2" x2="124.46" y2="76.2" width="0.1524" layer="91"/>
<pinref part="U$5" gate="G$1" pin="P26"/>
<label x="124.46" y="76.2" size="1.778" layer="95" xref="yes"/>
</segment>
<segment>
<wire x1="116.84" y1="33.02" x2="116.84" y2="35.56" width="0.1524" layer="91"/>
<pinref part="U$8" gate="G$1" pin="B59"/>
<label x="116.84" y="35.56" size="1.778" layer="95" rot="R90" xref="yes"/>
</segment>
</net>
<net name="E12" class="0">
<segment>
<wire x1="121.92" y1="73.66" x2="124.46" y2="73.66" width="0.1524" layer="91"/>
<pinref part="U$5" gate="G$1" pin="P27"/>
<label x="124.46" y="73.66" size="1.778" layer="95" xref="yes"/>
</segment>
<segment>
<wire x1="119.38" y1="33.02" x2="119.38" y2="35.56" width="0.1524" layer="91"/>
<pinref part="U$8" gate="G$1" pin="B60"/>
<label x="119.38" y="35.56" size="1.778" layer="95" rot="R90" xref="yes"/>
</segment>
</net>
<net name="E13" class="0">
<segment>
<wire x1="121.92" y1="71.12" x2="124.46" y2="71.12" width="0.1524" layer="91"/>
<pinref part="U$5" gate="G$1" pin="P28"/>
<label x="124.46" y="71.12" size="1.778" layer="95" xref="yes"/>
</segment>
<segment>
<wire x1="121.92" y1="33.02" x2="121.92" y2="35.56" width="0.1524" layer="91"/>
<pinref part="U$8" gate="G$1" pin="B61"/>
<label x="121.92" y="35.56" size="1.778" layer="95" rot="R90" xref="yes"/>
</segment>
</net>
<net name="E14" class="0">
<segment>
<wire x1="121.92" y1="68.58" x2="124.46" y2="68.58" width="0.1524" layer="91"/>
<pinref part="U$5" gate="G$1" pin="P29"/>
<label x="124.46" y="68.58" size="1.778" layer="95" xref="yes"/>
</segment>
<segment>
<wire x1="124.46" y1="33.02" x2="124.46" y2="35.56" width="0.1524" layer="91"/>
<pinref part="U$8" gate="G$1" pin="B62"/>
<label x="124.46" y="35.56" size="1.778" layer="95" rot="R90" xref="yes"/>
</segment>
</net>
<net name="E15" class="0">
<segment>
<wire x1="121.92" y1="66.04" x2="124.46" y2="66.04" width="0.1524" layer="91"/>
<pinref part="U$5" gate="G$1" pin="P30"/>
<label x="124.46" y="66.04" size="1.778" layer="95" xref="yes"/>
</segment>
<segment>
<wire x1="127" y1="33.02" x2="127" y2="35.56" width="0.1524" layer="91"/>
<pinref part="U$8" gate="G$1" pin="B63"/>
<label x="127" y="35.56" size="1.778" layer="95" rot="R90" xref="yes"/>
</segment>
</net>
<net name="!NRST!" class="0">
<segment>
<wire x1="187.96" y1="71.12" x2="185.42" y2="71.12" width="0.1524" layer="91"/>
<label x="185.42" y="71.12" size="1.778" layer="95" rot="MR0" xref="yes"/>
<pinref part="U$7" gate="G$1" pin="P12"/>
</segment>
<segment>
<wire x1="149.86" y1="104.14" x2="152.4" y2="104.14" width="0.1524" layer="91"/>
<pinref part="U$6" gate="G$1" pin="P15"/>
<label x="152.4" y="104.14" size="1.778" layer="95" xref="yes"/>
</segment>
</net>
<net name="F01" class="0">
<segment>
<wire x1="149.86" y1="101.6" x2="152.4" y2="101.6" width="0.1524" layer="91"/>
<pinref part="U$6" gate="G$1" pin="P16"/>
<label x="152.4" y="101.6" size="1.778" layer="95" xref="yes"/>
</segment>
<segment>
<wire x1="134.62" y1="5.08" x2="134.62" y2="2.54" width="0.1524" layer="91"/>
<pinref part="U$8" gate="G$1" pin="A66"/>
<label x="134.62" y="2.54" size="1.778" layer="95" rot="R270" xref="yes"/>
</segment>
</net>
<net name="F02" class="0">
<segment>
<wire x1="149.86" y1="99.06" x2="152.4" y2="99.06" width="0.1524" layer="91"/>
<pinref part="U$6" gate="G$1" pin="P17"/>
<label x="152.4" y="99.06" size="1.778" layer="95" xref="yes"/>
</segment>
<segment>
<wire x1="137.16" y1="5.08" x2="137.16" y2="2.54" width="0.1524" layer="91"/>
<pinref part="U$8" gate="G$1" pin="A67"/>
<label x="137.16" y="2.54" size="1.778" layer="95" rot="R270" xref="yes"/>
</segment>
</net>
<net name="F03" class="0">
<segment>
<wire x1="149.86" y1="96.52" x2="152.4" y2="96.52" width="0.1524" layer="91"/>
<pinref part="U$6" gate="G$1" pin="P18"/>
<label x="152.4" y="96.52" size="1.778" layer="95" xref="yes"/>
</segment>
<segment>
<wire x1="139.7" y1="5.08" x2="139.7" y2="2.54" width="0.1524" layer="91"/>
<pinref part="U$8" gate="G$1" pin="A68"/>
<label x="139.7" y="2.54" size="1.778" layer="95" rot="R270" xref="yes"/>
</segment>
</net>
<net name="F04" class="0">
<segment>
<wire x1="149.86" y1="93.98" x2="152.4" y2="93.98" width="0.1524" layer="91"/>
<pinref part="U$6" gate="G$1" pin="P19"/>
<label x="152.4" y="93.98" size="1.778" layer="95" xref="yes"/>
</segment>
<segment>
<wire x1="142.24" y1="5.08" x2="142.24" y2="2.54" width="0.1524" layer="91"/>
<pinref part="U$8" gate="G$1" pin="A69"/>
<label x="142.24" y="2.54" size="1.778" layer="95" rot="R270" xref="yes"/>
</segment>
</net>
<net name="F05" class="0">
<segment>
<wire x1="149.86" y1="91.44" x2="152.4" y2="91.44" width="0.1524" layer="91"/>
<pinref part="U$6" gate="G$1" pin="P20"/>
<label x="152.4" y="91.44" size="1.778" layer="95" xref="yes"/>
</segment>
<segment>
<wire x1="144.78" y1="5.08" x2="144.78" y2="2.54" width="0.1524" layer="91"/>
<pinref part="U$8" gate="G$1" pin="A70"/>
<label x="144.78" y="2.54" size="1.778" layer="95" rot="R270" xref="yes"/>
</segment>
</net>
<net name="F06" class="0">
<segment>
<wire x1="149.86" y1="88.9" x2="152.4" y2="88.9" width="0.1524" layer="91"/>
<pinref part="U$6" gate="G$1" pin="P21"/>
<label x="152.4" y="88.9" size="1.778" layer="95" xref="yes"/>
</segment>
<segment>
<wire x1="147.32" y1="5.08" x2="147.32" y2="2.54" width="0.1524" layer="91"/>
<pinref part="U$8" gate="G$1" pin="A71"/>
<label x="147.32" y="2.54" size="1.778" layer="95" rot="R270" xref="yes"/>
</segment>
</net>
<net name="F07" class="0">
<segment>
<wire x1="149.86" y1="86.36" x2="152.4" y2="86.36" width="0.1524" layer="91"/>
<pinref part="U$6" gate="G$1" pin="P22"/>
<label x="152.4" y="86.36" size="1.778" layer="95" xref="yes"/>
</segment>
<segment>
<wire x1="149.86" y1="5.08" x2="149.86" y2="2.54" width="0.1524" layer="91"/>
<pinref part="U$8" gate="G$1" pin="A72"/>
<label x="149.86" y="2.54" size="1.778" layer="95" rot="R270" xref="yes"/>
</segment>
</net>
<net name="F08" class="0">
<segment>
<wire x1="149.86" y1="83.82" x2="152.4" y2="83.82" width="0.1524" layer="91"/>
<pinref part="U$6" gate="G$1" pin="P23"/>
<label x="152.4" y="83.82" size="1.778" layer="95" xref="yes"/>
</segment>
<segment>
<wire x1="134.62" y1="33.02" x2="134.62" y2="35.56" width="0.1524" layer="91"/>
<pinref part="U$8" gate="G$1" pin="B66"/>
<label x="134.62" y="35.56" size="1.778" layer="95" rot="R90" xref="yes"/>
</segment>
</net>
<net name="F09" class="0">
<segment>
<wire x1="149.86" y1="81.28" x2="152.4" y2="81.28" width="0.1524" layer="91"/>
<pinref part="U$6" gate="G$1" pin="P24"/>
<label x="152.4" y="81.28" size="1.778" layer="95" xref="yes"/>
</segment>
<segment>
<pinref part="U$8" gate="G$1" pin="B67"/>
<wire x1="137.16" y1="33.02" x2="137.16" y2="35.56" width="0.1524" layer="91"/>
<label x="137.16" y="35.56" size="1.778" layer="95" rot="R90" xref="yes"/>
</segment>
</net>
<net name="F10" class="0">
<segment>
<wire x1="149.86" y1="78.74" x2="152.4" y2="78.74" width="0.1524" layer="91"/>
<pinref part="U$6" gate="G$1" pin="P25"/>
<label x="152.4" y="78.74" size="1.778" layer="95" xref="yes"/>
</segment>
<segment>
<pinref part="U$8" gate="G$1" pin="B68"/>
<wire x1="139.7" y1="33.02" x2="139.7" y2="35.56" width="0.1524" layer="91"/>
<label x="139.7" y="35.56" size="1.778" layer="95" rot="R90" xref="yes"/>
</segment>
</net>
<net name="F11" class="0">
<segment>
<wire x1="149.86" y1="76.2" x2="152.4" y2="76.2" width="0.1524" layer="91"/>
<pinref part="U$6" gate="G$1" pin="P26"/>
<label x="152.4" y="76.2" size="1.778" layer="95" xref="yes"/>
</segment>
<segment>
<pinref part="U$8" gate="G$1" pin="B69"/>
<wire x1="142.24" y1="33.02" x2="142.24" y2="35.56" width="0.1524" layer="91"/>
<label x="142.24" y="35.56" size="1.778" layer="95" rot="R90" xref="yes"/>
</segment>
</net>
<net name="F12" class="0">
<segment>
<wire x1="149.86" y1="73.66" x2="152.4" y2="73.66" width="0.1524" layer="91"/>
<pinref part="U$6" gate="G$1" pin="P27"/>
<label x="152.4" y="73.66" size="1.778" layer="95" xref="yes"/>
</segment>
<segment>
<pinref part="U$8" gate="G$1" pin="B70"/>
<wire x1="144.78" y1="33.02" x2="144.78" y2="35.56" width="0.1524" layer="91"/>
<label x="144.78" y="35.56" size="1.778" layer="95" rot="R90" xref="yes"/>
</segment>
</net>
<net name="F13" class="0">
<segment>
<wire x1="149.86" y1="71.12" x2="152.4" y2="71.12" width="0.1524" layer="91"/>
<pinref part="U$6" gate="G$1" pin="P28"/>
<label x="152.4" y="71.12" size="1.778" layer="95" xref="yes"/>
</segment>
<segment>
<pinref part="U$8" gate="G$1" pin="B71"/>
<wire x1="147.32" y1="33.02" x2="147.32" y2="35.56" width="0.1524" layer="91"/>
<label x="147.32" y="35.56" size="1.778" layer="95" rot="R90" xref="yes"/>
</segment>
</net>
<net name="F14" class="0">
<segment>
<wire x1="149.86" y1="68.58" x2="152.4" y2="68.58" width="0.1524" layer="91"/>
<pinref part="U$6" gate="G$1" pin="P29"/>
<label x="152.4" y="68.58" size="1.778" layer="95" xref="yes"/>
</segment>
<segment>
<pinref part="U$8" gate="G$1" pin="B72"/>
<wire x1="149.86" y1="33.02" x2="149.86" y2="35.56" width="0.1524" layer="91"/>
<label x="149.86" y="35.56" size="1.778" layer="95" rot="R90" xref="yes"/>
</segment>
</net>
<net name="F15" class="0">
<segment>
<wire x1="149.86" y1="66.04" x2="152.4" y2="66.04" width="0.1524" layer="91"/>
<pinref part="U$6" gate="G$1" pin="P30"/>
<label x="152.4" y="66.04" size="1.778" layer="95" xref="yes"/>
</segment>
<segment>
<pinref part="U$8" gate="G$1" pin="B73"/>
<wire x1="152.4" y1="33.02" x2="152.4" y2="35.56" width="0.1524" layer="91"/>
<label x="152.4" y="35.56" size="1.778" layer="95" rot="R90" xref="yes"/>
</segment>
</net>
<net name="VPP" class="0">
<segment>
<pinref part="CN1" gate="G$1" pin="1"/>
<wire x1="200.66" y1="139.7" x2="193.04" y2="139.7" width="0.1524" layer="91"/>
<label x="193.04" y="139.7" size="1.778" layer="95" rot="MR0" xref="yes"/>
</segment>
<segment>
<wire x1="200.66" y1="119.38" x2="193.04" y2="119.38" width="0.1524" layer="91"/>
<label x="193.04" y="119.38" size="1.778" layer="95" rot="MR0" xref="yes"/>
<pinref part="CN2" gate="G$1" pin="1"/>
</segment>
<segment>
<pinref part="U$1" gate="G$1" pin="P1"/>
<wire x1="10.16" y1="139.7" x2="12.7" y2="139.7" width="0.1524" layer="91"/>
<label x="12.7" y="139.7" size="1.778" layer="95" xref="yes"/>
</segment>
<segment>
<wire x1="38.1" y1="139.7" x2="40.64" y2="139.7" width="0.1524" layer="91"/>
<label x="40.64" y="139.7" size="1.778" layer="95" xref="yes"/>
<pinref part="U$2" gate="G$1" pin="P1"/>
</segment>
<segment>
<wire x1="66.04" y1="139.7" x2="68.58" y2="139.7" width="0.1524" layer="91"/>
<label x="68.58" y="139.7" size="1.778" layer="95" xref="yes"/>
<pinref part="U$3" gate="G$1" pin="P1"/>
</segment>
<segment>
<wire x1="93.98" y1="139.7" x2="96.52" y2="139.7" width="0.1524" layer="91"/>
<label x="96.52" y="139.7" size="1.778" layer="95" xref="yes"/>
<pinref part="U$4" gate="G$1" pin="P1"/>
</segment>
<segment>
<wire x1="121.92" y1="139.7" x2="124.46" y2="139.7" width="0.1524" layer="91"/>
<label x="124.46" y="139.7" size="1.778" layer="95" xref="yes"/>
<pinref part="U$5" gate="G$1" pin="P1"/>
</segment>
<segment>
<wire x1="149.86" y1="139.7" x2="152.4" y2="139.7" width="0.1524" layer="91"/>
<label x="152.4" y="139.7" size="1.778" layer="95" xref="yes"/>
<pinref part="U$6" gate="G$1" pin="P1"/>
</segment>
</net>
<net name="T_VCC" class="0">
<segment>
<wire x1="187.96" y1="93.98" x2="185.42" y2="93.98" width="0.1524" layer="91"/>
<label x="185.42" y="93.98" size="1.778" layer="95" rot="MR0" xref="yes"/>
<pinref part="U$7" gate="G$1" pin="P3"/>
</segment>
</net>
<net name="JTMS/SWDIO" class="0">
<segment>
<wire x1="187.96" y1="91.44" x2="185.42" y2="91.44" width="0.1524" layer="91"/>
<label x="185.42" y="91.44" size="1.778" layer="95" rot="MR0" xref="yes"/>
<pinref part="U$7" gate="G$1" pin="P4"/>
</segment>
<segment>
<wire x1="149.86" y1="116.84" x2="152.4" y2="116.84" width="0.1524" layer="91"/>
<pinref part="U$6" gate="G$1" pin="P10"/>
<label x="152.4" y="116.84" size="1.778" layer="95" xref="yes"/>
</segment>
</net>
<net name="JCLK/SWCLK" class="0">
<segment>
<wire x1="185.42" y1="86.36" x2="187.96" y2="86.36" width="0.1524" layer="91"/>
<label x="185.42" y="86.36" size="1.778" layer="95" rot="MR0" xref="yes"/>
<pinref part="U$7" gate="G$1" pin="P6"/>
</segment>
<segment>
<wire x1="149.86" y1="114.3" x2="152.4" y2="114.3" width="0.1524" layer="91"/>
<pinref part="U$6" gate="G$1" pin="P11"/>
<label x="152.4" y="114.3" size="1.778" layer="95" xref="yes"/>
</segment>
</net>
<net name="JTDO/SWO" class="0">
<segment>
<wire x1="187.96" y1="81.28" x2="185.42" y2="81.28" width="0.1524" layer="91"/>
<label x="185.42" y="81.28" size="1.778" layer="95" rot="MR0" xref="yes"/>
<pinref part="U$7" gate="G$1" pin="P8"/>
</segment>
<segment>
<wire x1="149.86" y1="109.22" x2="152.4" y2="109.22" width="0.1524" layer="91"/>
<pinref part="U$6" gate="G$1" pin="P13"/>
<label x="152.4" y="109.22" size="1.778" layer="95" xref="yes"/>
</segment>
</net>
<net name="JCLK" class="0">
<segment>
<wire x1="187.96" y1="78.74" x2="185.42" y2="78.74" width="0.1524" layer="91"/>
<label x="185.42" y="78.74" size="1.778" layer="95" rot="MR0" xref="yes"/>
<pinref part="U$7" gate="G$1" pin="P9"/>
</segment>
</net>
<net name="JTDI" class="0">
<segment>
<wire x1="187.96" y1="76.2" x2="185.42" y2="76.2" width="0.1524" layer="91"/>
<label x="185.42" y="76.2" size="1.778" layer="95" rot="MR0" xref="yes"/>
<pinref part="U$7" gate="G$1" pin="P10"/>
</segment>
<segment>
<wire x1="149.86" y1="111.76" x2="152.4" y2="111.76" width="0.1524" layer="91"/>
<pinref part="U$6" gate="G$1" pin="P12"/>
<label x="152.4" y="111.76" size="1.778" layer="95" xref="yes"/>
</segment>
</net>
<net name="VCP_RX" class="0">
<segment>
<wire x1="187.96" y1="68.58" x2="185.42" y2="68.58" width="0.1524" layer="91"/>
<label x="185.42" y="68.58" size="1.778" layer="95" rot="MR0" xref="yes"/>
<pinref part="U$7" gate="G$1" pin="P13"/>
</segment>
</net>
<net name="VCP_TX" class="0">
<segment>
<wire x1="187.96" y1="66.04" x2="185.42" y2="66.04" width="0.1524" layer="91"/>
<label x="185.42" y="66.04" size="1.778" layer="95" rot="MR0" xref="yes"/>
<pinref part="U$7" gate="G$1" pin="P14"/>
</segment>
</net>
<net name="N$180" class="0">
<segment>
<wire x1="154.94" y1="33.02" x2="154.94" y2="35.56" width="0.1524" layer="91"/>
<pinref part="U$8" gate="G$1" pin="B74"/>
</segment>
</net>
<net name="N$181" class="0">
<segment>
<wire x1="157.48" y1="33.02" x2="157.48" y2="35.56" width="0.1524" layer="91"/>
<pinref part="U$8" gate="G$1" pin="B75"/>
</segment>
</net>
<net name="N$189" class="0">
<segment>
<wire x1="154.94" y1="33.02" x2="154.94" y2="35.56" width="0.1524" layer="91"/>
</segment>
</net>
<net name="N$190" class="0">
<segment>
<wire x1="157.48" y1="33.02" x2="157.48" y2="35.56" width="0.1524" layer="91"/>
</segment>
</net>
<net name="N$191" class="0">
<segment>
<wire x1="160.02" y1="33.02" x2="160.02" y2="35.56" width="0.1524" layer="91"/>
<pinref part="U$8" gate="G$1" pin="B76"/>
</segment>
</net>
<net name="N$192" class="0">
<segment>
<wire x1="162.56" y1="33.02" x2="162.56" y2="35.56" width="0.1524" layer="91"/>
<pinref part="U$8" gate="G$1" pin="B77"/>
</segment>
</net>
<net name="N$193" class="0">
<segment>
<wire x1="165.1" y1="33.02" x2="165.1" y2="35.56" width="0.1524" layer="91"/>
<pinref part="U$8" gate="G$1" pin="B78"/>
</segment>
</net>
<net name="N$194" class="0">
<segment>
<wire x1="167.64" y1="33.02" x2="167.64" y2="35.56" width="0.1524" layer="91"/>
<pinref part="U$8" gate="G$1" pin="B79"/>
</segment>
</net>
<net name="N$195" class="0">
<segment>
<wire x1="170.18" y1="33.02" x2="170.18" y2="35.56" width="0.1524" layer="91"/>
<pinref part="U$8" gate="G$1" pin="B80"/>
</segment>
</net>
<net name="N$196" class="0">
<segment>
<wire x1="172.72" y1="33.02" x2="172.72" y2="35.56" width="0.1524" layer="91"/>
<pinref part="U$8" gate="G$1" pin="B81"/>
</segment>
</net>
<net name="N$197" class="0">
<segment>
<wire x1="175.26" y1="33.02" x2="175.26" y2="35.56" width="0.1524" layer="91"/>
<pinref part="U$8" gate="G$1" pin="B82"/>
</segment>
</net>
<net name="B01" class="0">
<segment>
<wire x1="33.02" y1="5.08" x2="33.02" y2="2.54" width="0.1524" layer="91"/>
<pinref part="U$8" gate="G$1" pin="A26"/>
<label x="33.02" y="2.54" size="1.778" layer="95" rot="R270" xref="yes"/>
</segment>
<segment>
<wire x1="38.1" y1="101.6" x2="40.64" y2="101.6" width="0.1524" layer="91"/>
<pinref part="U$2" gate="G$1" pin="P16"/>
<label x="40.64" y="101.6" size="1.778" layer="95" xref="yes"/>
</segment>
</net>
<net name="B02" class="0">
<segment>
<wire x1="35.56" y1="5.08" x2="35.56" y2="2.54" width="0.1524" layer="91"/>
<pinref part="U$8" gate="G$1" pin="A27"/>
<label x="35.56" y="2.54" size="1.778" layer="95" rot="R270" xref="yes"/>
</segment>
<segment>
<wire x1="38.1" y1="99.06" x2="40.64" y2="99.06" width="0.1524" layer="91"/>
<pinref part="U$2" gate="G$1" pin="P17"/>
<label x="40.64" y="99.06" size="1.778" layer="95" xref="yes"/>
</segment>
</net>
<net name="B03" class="0">
<segment>
<wire x1="38.1" y1="5.08" x2="38.1" y2="2.54" width="0.1524" layer="91"/>
<pinref part="U$8" gate="G$1" pin="A28"/>
<label x="38.1" y="2.54" size="1.778" layer="95" rot="R270" xref="yes"/>
</segment>
<segment>
<wire x1="38.1" y1="96.52" x2="40.64" y2="96.52" width="0.1524" layer="91"/>
<pinref part="U$2" gate="G$1" pin="P18"/>
<label x="40.64" y="96.52" size="1.778" layer="95" xref="yes"/>
</segment>
</net>
<net name="B04" class="0">
<segment>
<wire x1="40.64" y1="2.54" x2="40.64" y2="5.08" width="0.1524" layer="91"/>
<pinref part="U$8" gate="G$1" pin="A29"/>
<label x="40.64" y="2.54" size="1.778" layer="95" rot="R270" xref="yes"/>
</segment>
<segment>
<wire x1="38.1" y1="93.98" x2="40.64" y2="93.98" width="0.1524" layer="91"/>
<pinref part="U$2" gate="G$1" pin="P19"/>
<label x="40.64" y="93.98" size="1.778" layer="95" xref="yes"/>
</segment>
</net>
<net name="B05" class="0">
<segment>
<wire x1="43.18" y1="5.08" x2="43.18" y2="2.54" width="0.1524" layer="91"/>
<pinref part="U$8" gate="G$1" pin="A30"/>
<label x="43.18" y="2.54" size="1.778" layer="95" rot="R270" xref="yes"/>
</segment>
<segment>
<wire x1="38.1" y1="91.44" x2="40.64" y2="91.44" width="0.1524" layer="91"/>
<pinref part="U$2" gate="G$1" pin="P20"/>
<label x="40.64" y="91.44" size="1.778" layer="95" xref="yes"/>
</segment>
</net>
<net name="B06" class="0">
<segment>
<wire x1="45.72" y1="5.08" x2="45.72" y2="2.54" width="0.1524" layer="91"/>
<pinref part="U$8" gate="G$1" pin="A31"/>
<label x="45.72" y="2.54" size="1.778" layer="95" rot="R270" xref="yes"/>
</segment>
<segment>
<wire x1="38.1" y1="88.9" x2="40.64" y2="88.9" width="0.1524" layer="91"/>
<pinref part="U$2" gate="G$1" pin="P21"/>
<label x="40.64" y="88.9" size="1.778" layer="95" xref="yes"/>
</segment>
</net>
<net name="B07" class="0">
<segment>
<wire x1="48.26" y1="5.08" x2="48.26" y2="2.54" width="0.1524" layer="91"/>
<pinref part="U$8" gate="G$1" pin="A32"/>
<label x="48.26" y="2.54" size="1.778" layer="95" rot="R270" xref="yes"/>
</segment>
<segment>
<wire x1="38.1" y1="86.36" x2="40.64" y2="86.36" width="0.1524" layer="91"/>
<pinref part="U$2" gate="G$1" pin="P22"/>
<label x="40.64" y="86.36" size="1.778" layer="95" xref="yes"/>
</segment>
</net>
<net name="N$259" class="0">
<segment>
<wire x1="152.4" y1="5.08" x2="152.4" y2="2.54" width="0.1524" layer="91"/>
<pinref part="U$8" gate="G$1" pin="A73"/>
</segment>
</net>
<net name="N$260" class="0">
<segment>
<wire x1="154.94" y1="2.54" x2="154.94" y2="5.08" width="0.1524" layer="91"/>
<pinref part="U$8" gate="G$1" pin="A74"/>
</segment>
</net>
<net name="N$261" class="0">
<segment>
<wire x1="154.94" y1="5.08" x2="154.94" y2="2.54" width="0.1524" layer="91"/>
</segment>
</net>
<net name="N$262" class="0">
<segment>
<wire x1="157.48" y1="5.08" x2="157.48" y2="2.54" width="0.1524" layer="91"/>
<pinref part="U$8" gate="G$1" pin="A75"/>
</segment>
</net>
<net name="N$263" class="0">
<segment>
<wire x1="160.02" y1="5.08" x2="160.02" y2="2.54" width="0.1524" layer="91"/>
<pinref part="U$8" gate="G$1" pin="A76"/>
</segment>
</net>
<net name="N$264" class="0">
<segment>
<wire x1="162.56" y1="5.08" x2="162.56" y2="2.54" width="0.1524" layer="91"/>
<pinref part="U$8" gate="G$1" pin="A77"/>
</segment>
</net>
<net name="N$265" class="0">
<segment>
<wire x1="165.1" y1="5.08" x2="165.1" y2="2.54" width="0.1524" layer="91"/>
<pinref part="U$8" gate="G$1" pin="A78"/>
</segment>
</net>
<net name="N$266" class="0">
<segment>
<wire x1="167.64" y1="5.08" x2="167.64" y2="2.54" width="0.1524" layer="91"/>
<pinref part="U$8" gate="G$1" pin="A79"/>
</segment>
</net>
<net name="N$267" class="0">
<segment>
<wire x1="170.18" y1="5.08" x2="170.18" y2="2.54" width="0.1524" layer="91"/>
<pinref part="U$8" gate="G$1" pin="A80"/>
</segment>
</net>
<net name="N$268" class="0">
<segment>
<wire x1="172.72" y1="5.08" x2="172.72" y2="2.54" width="0.1524" layer="91"/>
<pinref part="U$8" gate="G$1" pin="A81"/>
</segment>
</net>
<net name="N$269" class="0">
<segment>
<wire x1="175.26" y1="2.54" x2="175.26" y2="5.08" width="0.1524" layer="91"/>
<pinref part="U$8" gate="G$1" pin="A82"/>
</segment>
</net>
<net name="!JNTRST!" class="0">
<segment>
<pinref part="U$6" gate="G$1" pin="P14"/>
<wire x1="149.86" y1="106.68" x2="152.4" y2="106.68" width="0.1524" layer="91"/>
<label x="152.4" y="106.68" size="1.778" layer="95" xref="yes"/>
</segment>
</net>
</nets>
</sheet>
</sheets>
</schematic>
</drawing>
<compatibility>
<note version="8.2" severity="warning">
Since Version 8.2, EAGLE supports online libraries. The ids
of those online libraries will not be understood (or retained)
with this version.
</note>
<note version="8.3" severity="warning">
Since Version 8.3, EAGLE supports URNs for individual library
assets (packages, symbols, and devices). The URNs of those assets
will not be understood (or retained) with this version.
</note>
</compatibility>
</eagle>
