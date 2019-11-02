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
<library name="pins">
<packages>
<package name="P2_7_1.27">
<pad name="P1" x="-1.27" y="7.62" drill="0.65"/>
<pad name="P2" x="-1.27" y="5.08" drill="0.65"/>
<pad name="P3" x="-1.27" y="2.54" drill="0.65"/>
<pad name="P4" x="-1.27" y="0" drill="0.65"/>
<pad name="P5" x="-1.27" y="-2.54" drill="0.65"/>
<pad name="P6" x="-1.27" y="-5.08" drill="0.65"/>
<pad name="P7" x="-1.27" y="-7.62" drill="0.65"/>
<pad name="P8" x="1.27" y="7.62" drill="0.65"/>
<pad name="P9" x="1.27" y="5.08" drill="0.65"/>
<pad name="P10" x="1.27" y="2.54" drill="0.65"/>
<pad name="P11" x="1.27" y="0" drill="0.65"/>
<pad name="P12" x="1.27" y="-2.54" drill="0.65"/>
<pad name="P13" x="1.27" y="-5.08" drill="0.65"/>
<pad name="P14" x="1.27" y="-7.62" drill="0.65"/>
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
<part name="U$7" library="pins" deviceset="P2_7_1.27" device=""/>
<part name="CN1" library="jst-ph" deviceset="B4B-PH-*" device="K-S"/>
<part name="CN2" library="jst-ph" deviceset="B4B-PH-*" device="K-S"/>
<part name="U$8" library="con-pci_express(pci-e)" deviceset="PCI-E16X_DATA_EDGE" device=""/>
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
<instance part="U$2" gate="G$1" x="5.08" y="17.78" smashed="yes">
<attribute name="NAME" x="-2.54" y="58.674" size="1.27" layer="95"/>
<attribute name="VALUE" x="-2.54" y="-22.86" size="1.27" layer="96"/>
</instance>
<instance part="U$3" gate="G$1" x="5.08" y="-66.04" smashed="yes">
<attribute name="NAME" x="-2.54" y="-25.146" size="1.27" layer="95"/>
<attribute name="VALUE" x="-2.54" y="-106.68" size="1.27" layer="96"/>
</instance>
<instance part="U$4" gate="G$1" x="5.08" y="-149.86" smashed="yes">
<attribute name="NAME" x="-2.54" y="-108.966" size="1.27" layer="95"/>
<attribute name="VALUE" x="-2.54" y="-190.5" size="1.27" layer="96"/>
</instance>
<instance part="U$5" gate="G$1" x="5.08" y="-233.68" smashed="yes">
<attribute name="NAME" x="-2.54" y="-192.786" size="1.27" layer="95"/>
<attribute name="VALUE" x="-2.54" y="-274.32" size="1.27" layer="96"/>
</instance>
<instance part="U$6" gate="G$1" x="5.08" y="-317.5" smashed="yes">
<attribute name="NAME" x="-2.54" y="-276.606" size="1.27" layer="95"/>
<attribute name="VALUE" x="-2.54" y="-358.14" size="1.27" layer="96"/>
</instance>
<instance part="U$7" gate="G$1" x="172.72" y="-281.94" smashed="yes">
<attribute name="NAME" x="165.1" y="-263.906" size="1.27" layer="95"/>
<attribute name="VALUE" x="165.1" y="-304.8" size="1.27" layer="96"/>
</instance>
<instance part="CN1" gate="G$1" x="127" y="-246.38" smashed="yes">
<attribute name="NAME" x="123.19" y="-240.03" size="1.778" layer="95"/>
<attribute name="VALUE" x="123.19" y="-256.54" size="1.778" layer="96"/>
</instance>
<instance part="CN2" gate="G$1" x="152.4" y="-246.38" smashed="yes">
<attribute name="NAME" x="148.59" y="-240.03" size="1.778" layer="95"/>
<attribute name="VALUE" x="148.59" y="-256.54" size="1.778" layer="96"/>
</instance>
<instance part="U$8" gate="G$1" x="119.38" y="-12.7" smashed="yes">
<attribute name="NAME" x="121.92" y="-20.32" size="1.27" layer="95" rot="R90"/>
<attribute name="VALUE" x="121.92" y="17.78" size="1.27" layer="96" rot="R90"/>
</instance>
</instances>
<busses>
</busses>
<nets>
</nets>
</sheet>
</sheets>
</schematic>
</drawing>
</eagle>
