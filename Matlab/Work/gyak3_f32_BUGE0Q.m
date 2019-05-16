function [abra, hitelesitettMeresiErtekek, elsoSzenzorHelyesMereseiSzovegben,szenzorokDeliMeresenekAtlagaSzovegben]=gyak3_f32_BUGE0Q(legnyomasErtekek)
% A bemenetünk egy 900 és 1060 közötti véletlenszerű értékeket tartalmazó
% 4x3x31-es mátrix.
%% Ide jöhet az 1. részfeladathoz szükséges adat kigyűjtése

elsoesti = squeeze(legnyomasErtekek(1,3,:));

he= find(930<=elsoesti & elsoesti<=1060);


%% Ide kerüljön az ábra kirajzoltatása
abra = figure; % ez után
hold on;
axis([1 31 890 1100]);
xlabel('napok száma','FontSize', 12,'FontWeight', 'bold');
ylabel('légköri nyomás [hPa]','FontSize', 12,'FontWeight', 'bold');
title('Első szenzor, esti mérés, minden nap', 'FontSize', 14,'FontWeight', 'bold');
plot([1,31],[1060,1060],'m','LineWidth',2);
plot([1,31],[930,930],'m','LineWidth',2);
plot(elsoesti,'k -. o','LineWidth',3,'MarkerSize',7);
plot(he,elsoesti(he),'o','LineWidth',2,'MarkerSize',7,'MarkerEdgeColor','r','MarkerFaceColor','g');
hold off;

%% Itt legyenek a további részfeladatok

hitelesitettMeresiErtekek= 930<=legnyomasErtekek & legnyomasErtekek<=1060;
hitelesitettMeresiErtekek= legnyomasErtekek.*hitelesitettMeresiErtekek;

eshms = length(find(hitelesitettMeresiErtekek(1,3,11:20)>0));

elsoSzenzorHelyesMereseiSzovegben = sprintf('Helyes mérési értékek darabszáma (első szenzor, esti mérés, 11-20. napokra): %1.0f',eshms);

d2 = squeeze(legnyomasErtekek(2,2,:));
d3 = squeeze(legnyomasErtekek(3,2,:));
d4 = squeeze(legnyomasErtekek(4,2,:));

d2 = mean(d2(find(930<=d2 & d2<=1060)));
d3 = mean(d3(find(930<=d3 & d3<=1060)));
d4 = mean(d4(find(930<=d4 & d4<=1060)));

szenzorokDeliMeresenekAtlagaSzovegben = sprintf('A második szenzor déli átlaga: +%4.3f, a harmadiknak: +%4.3f és a negyediknek: +%4.3f',d2,d3,d4);
end
